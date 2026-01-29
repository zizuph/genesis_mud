/*
 * /d/Gondor/events/npc.c
 *
 * Standard object base for events.
 *
 * NOTE! When making changes to this file, you must update
 * the file rather than load it for the event wand to work
 * right!
 *
 * Gwyneth September 27, 2000
 */

inherit "/std/monster";

#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

#include "../events.h"

int intro = 1;

public void
create_monster()
{
    add_name("npc");
    add_name("event_npc");
    set_race_name("npc");
    set_living_name("event_npc");
    set_long("This is a generic npc for events.\n");
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    set_tell_active(1);
    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_SEE_DARK, 4);

    setuid();
    seteuid(getuid());

    clone_object(EVENTOBJ + "replier")->move(this_object(), 1);
}

/*
 * Function name: query_option
 * Description  : Use this to emulate the echo option.
 * Arguments    : int option - the option to check.
 * Returns      : int 1/0 - true/false.
 */
int
query_option(int option)
{
   if (option == OPT_ECHO)
   {
        return 1;
   }
   return 0;
}

void
living_name(string str)
{
    set_living_name(str);
}

void
intro_toggle(string str)
{
    str = lower_case(str);

    switch(str)
    {
        case "y":
        case "yes":
            intro = 1;
        default:
            intro = 0;
    }

    return;
}

int
intro_status()
{
    return intro;
}

string
query_recover()
{
    return 0;
}

public void
set_intro(int i)
{
    intro = i;
}

public int
query_intro()
{
    return intro;
}

public void
introduce(object player = this_player())
{
    if (!objectp(player) ||
      !interactive(player) ||
      !present(player, environment(this_object())) ||
      query_prop(OBJ_I_HIDE) || !intro)
    {
        return;
    }

    command("introduce myself to " + OB_NAME(player));
    return;
}

public void
add_introduced(string str)
{
    object who;

    if (this_object()->query_prop(OBJ_I_HIDE))
    {
        return;
    }

    if (intro && objectp(who = find_player(str)))
    {
        set_alarm(2.0, 0.0, &introduce(who));
        return;
    }
}

public int
do_glance(int brief)
{
    object env;
    string item;

    env = environment();
    if (stringp(env->query_prop(OBJ_S_WIZINFO)))
    {
        write("Wizinfo ");
    }

    write(file_name(env) + "\n");

    if (!CAN_SEE_IN_ROOM(this_object()))
    {
        if (!stringp(item = env->query_prop(ROOM_S_DARK_LONG)))
        {
            write("It's too dark to see, but here is what it would look " +
                "like if you could:\n");
        }
        else
        {
            write(item);
        }
    }
   /* Describe the room and its contents. */ 
#ifdef DAY_AND_NIGHT
    if (!env->query_prop(ROOM_I_INSIDE) &&
        ((HOUR > 21) ||
         (HOUR < 5)) &&
        ((env->query_prop(OBJ_I_LIGHT) +
         query_prop(LIVE_I_SEE_DARK)) < 2))
    {
        write("It's too dark to see.\n");
    }
    else
#endif
    {
        if (brief)
        {
            write(capitalize(env->short()) + ".\n");
 
            if (!env->query_noshow_obvious())
            {
                write(env->exits_description());
            }
        }
        else
        {
            write(env->long());
        }
    }
 
    env->show_visible_contents(this_object());
 
    /* Give a nice description of the combat that is going on. */
    describe_combat(FILTER_LIVE(all_inventory(env))); 
 
    return 1;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    ::move_living(how, to_dest, dont_follow, no_glance);

    if (!interactive())
    {
        this_object()->do_glance(0);
    }
}
