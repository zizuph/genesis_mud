/*
No move object for when someone joins the OotS

Based on Viridian's stun, which was based on an old
dragonfear stun.

Arman - 2017
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

public int no_command();

int time;

object victim;


create_object() 
{
    seteuid(getuid());
    set_name("Elistan_dialogue_no_move_obj");

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
      "mount"});

    if (TP->query_wiz_level())
	return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
	return 0;
    else
	return no_command();

    return 1;
}


int
no_command()
{
    write("You can't leave until Elistan has indoctrinated you into the Holy " +
       "Order of the Stars.\n");
    return 1;
}


void
remove_dialogue_no_move(object victim)
{
    object vict = victim; 

    vict->catch_msg("You feel a sense of purpose that was missing before, and " +
        "a fervour to spread the teachings of the Old Gods into the world again.\n");

    remove_object();
}


void
do_dialogue_no_move()
{
    int time;

    time = 8;

    set_alarm(itof(time), 0.0, "remove_dialogue_no_move", victim);
    time = 0;
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

    if(!living(to))
    {
	remove_object();
	return;
    }

    victim = to;
    do_dialogue_no_move();
}
