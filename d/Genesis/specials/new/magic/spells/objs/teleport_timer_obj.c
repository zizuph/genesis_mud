/*
 *  Teleport timer, restricting how regularly people can be teleported.
 *
 *  Zizuph Nov 2021
 *
 *  Aug 2022 - track up to 3 teleports instead of one.
 *
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

#define MAX_TELEPORTS 3
#define TELEPORT_TIMER_SUBLOC  "teleport_timer"

int* expiration_times = ({});

int alarm_id = 0;

void remove_teleport_timer();

create_object() 
{
    seteuid(getuid());
    set_name("_teleport_timer_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

int is_teleport_blocked()
{
    return sizeof(expiration_times) >= MAX_TELEPORTS;
}

private void schedule_alarm()
{
    if (!alarm_id && sizeof(expiration_times))
    {
        alarm_id = set_alarm(itof(expiration_times[0] - time() + 1), 0.0, remove_teleport_timer);
    }
}

void add_teleport_delay(int delay)
{
    int start = time();
    if (sizeof(expiration_times))
    {
        start = expiration_times[sizeof(expiration_times) - 1];
    }
    expiration_times += ({ start + delay });
    schedule_alarm();
}

void notify_teleport_timer_gone()
{
    if (sizeof(expiration_times))
    {
        environment(this_object())->
            catch_msg("You feel less affected by your prior teleportation.\n");
    }
    else
    {
        environment(this_object())->
            catch_msg("You are no longer affected by your prior " +
            "teleportation.\n");
        environment(this_object())->remove_subloc(TELEPORT_TIMER_SUBLOC);
        remove_object();
    }
}

void
init_arg(string arg)
{
    string time_str;
    string* times;
	sscanf(arg, "#TIMER#%s", time_str);
    times = explode(time_str, " ");
    int removed_timer = 0;
    foreach (string str : times)
    {
        int alarm_time = atoi(str);
        if (alarm_time > 0)
        {
            if (alarm_time > time())
            {
                expiration_times += ({ alarm_time });
            }
            else
            {
                removed_timer = 1;
            }
        }
    }
    if (removed_timer)
    {
        set_alarm(0.1, 0.0, notify_teleport_timer_gone);
    }
    schedule_alarm();
}
mixed
query_auto_load()
{
    // sprintf format: " 123 124 125"
	return (MASTER + ":#TIMER#" + sprintf("%@ d", expiration_times));
}

public void enter_env(object dest, object old)
{
    if (dest)
        dest->add_subloc(TELEPORT_TIMER_SUBLOC, this_object());
}

public string vitals_description()
{
    switch (sizeof(expiration_times))
    {
        case 0:
          return "You feel unaffected by prior teleportation.\n";
        case 1:
          return "You feel slightly affected by prior teleportation.\n";
        case 2:
          return "You feel affected by prior teleportation.\n";
        default:
          return "You feel heavily affected by prior teleportation.\n";
    }
    return "";
}


public string show_subloc(string subloc, object on, object for_obj)
{
    if (subloc != TELEPORT_TIMER_SUBLOC)
        return "";
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    
    if (for_obj != on)
        return "";
    return vitals_description();
}

void
remove_teleport_timer()
{
    expiration_times = expiration_times[1..];
    alarm_id = 0;
    notify_teleport_timer_gone();
    if (!sizeof(expiration_times))
    {
    }
    else
    {
        schedule_alarm();
    }
}

public int show_teleport(string arg)
{
    if (!strlen(arg) || arg == "all")
    {
        write(vitals_description());
    }
    return 0;
}

void init()
{
    ::init();
    add_action(show_teleport, "v");
    add_action(show_teleport, "vitals");
}
