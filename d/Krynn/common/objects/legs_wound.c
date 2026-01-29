/*
    A lethal flame-bladed glaive's stun. It makes the person unable to
    move for a short while.

    Idea from dragon fear coded by Erine & Jeremiah.

    Blizzard, 28/06/2003
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
    set_name("Legs_Wound");

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

    not_allowed = ({"n", "north", "s", "south", "w", "west", "e", "east",
      "nw", "northwest", "sw", "southwest", "se", "southeast", "mount",
      "northeast", "ne", "u", "up", "d", "down", "in", "out", "enter",
      "climb", "common", "tailor", "stall", "board", "disembark", "jump",
      "inn" });

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
    write("Your legs have been wounded badly, you still can not move.\n");
    return 1;
}


void
remove_wound(object victim)
{
    object vict = victim; 

    vict->catch_msg("The pain in your legs wears off.\n");

/*    tell_room(E(vict), QCTNAME(vict) + " appears able to move " +
             "again.\n", vict, TO);
 */
    remove_object();
}


void
do_wound()
{
    int time;

    time = 5 + random(5);

    victim->catch_msg("You feel a terrible pain in your legs!\n");

    if(victim->query_wiz_level())
    {
	victim->catch_msg("As a wizard, you ignore the pain.\n");
        remove_object();
        return;
    }

    tell_room(E(victim), QCTNAME(victim) + " grimaces painfully.\n", 
        victim, TO);

    set_alarm(itof(time), 0.0, &remove_wound(victim));
    time = 0;
}


void
enter_env(object obj, object from)
{
    ::enter_env(obj, from);
    if( !objectp(obj) )
    {
	remove_object();
	return;
    }

    if( !living(obj) )
    {
	remove_object();
	return;
    }

    victim = obj;
    do_wound();
}

