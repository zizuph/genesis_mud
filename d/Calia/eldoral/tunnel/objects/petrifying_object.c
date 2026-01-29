inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

public int no_command();

int dispel_alarm;
int original_time;
object victim;

create_object() 
{
    seteuid(getuid());
    set_name("_petrifying_object");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}

init()
{
    ::init();
    add_action("do_all_commands", "", 1);
}


public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"n","north","s","south","w","west","e","east","nw",
                    "northwest","sw","southwest","se","southeast",
                    "northeast","ne","u","up","d","down","teleport",
                    "goto","home","say","rsay","ksay","ponder",
                    "project", "cast"});

    if (this_player()->query_wiz_level())
        return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
    {
        return 0;
    }
    else
    {
        return no_command();
    }
}


int
no_command()
{
    write("You are encapsulated in a stone shell, you are unable to do that.\n");
    return 1;
}


void
remove_petrification(object victim)
{
    victim->catch_tell("You manage to force your limps to move, " +
		       "you feel the stone shell shatter and disappear.\n");
    victim->remove_stun();
    remove_object();
}

void
do_petrification()
{
    int time;

    time = 25 + random(10);
    original_time = time;
    victim->catch_tell("You feel the particles on your body harden as it forms " +
		      "a stone shell around you.\nYou can no longer move.\n");
    victim->add_stun();

    dispel_alarm = set_alarm(itof(time), 0.0, "remove_petrification", victim);
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
        remove_object();
        return;
    }

    if(!interactive(to))
    {
        remove_object();
        return;
    }

    victim = to;
    do_petrification();
}

void
renew_time()
{
    remove_alarm(dispel_alarm);
    dispel_alarm = set_alarm(itof(original_time), 0.0, "remove_petrification", victim);
    victim->catch_tell("You feel the stone shell around you strengthen.\n");
}
