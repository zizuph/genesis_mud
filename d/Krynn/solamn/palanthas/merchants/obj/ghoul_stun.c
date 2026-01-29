/*
Ghoul stun in Shoikan Grove

Coded : 7/18 by Arman
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

public int no_command();
int time;
object victim;

create_object() 
{
    seteuid(getuid());
    set_name("shoikan_ghoul_stun");

    add_item(({"ghoulish hands","hands"}),
        "Ghoulish hands reach out of the damp ground of the " +
        "Shoikan Grove, holding tightly to your legs and trying " +
        "to pull you down into the earth!\n");

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
    write("Ghoulish hands rising out of the ground hold you tightly! " +
        "You can't leave in that direction!\n");
    return 1;
}


public void
remove_ghoul_stun(object victim)
{
    object vict = victim; 

    vict->catch_msg("The ghoulish hands let go and withdraw into the " +
        "ground.\n");
    tell_room(E(victim), "The ghoulish hands let go of " +QTNAME(victim)+ 
        " and withdraw into the ground.\n", victim, TO);

    remove_object();
}


void
do_ghoul_stun()
{
    time = 180;

    victim->catch_msg("As you reach towards the half-buried decaying corpse " +
        "ghoulish hands explode out of the ground, grabbing " +
        "your legs in an attempt to pull you down into the earth!\n");
    tell_room(E(victim), "Ghoulish hands explode out of the ground and grab " +
        QTNAME(victim)+ ", restraining " + HIM(victim) + " and trying to pull " +
        HIM(victim)+ " down into the earth!\n", victim, TO);

    if(victim->query_wiz_level())
	victim->catch_msg("As a wizard, you are immune to being stunned.\n");

    if (victim->query_wiz_level())
	tell_room(E(victim), C(PRONOUN(victim)) + " is a wizard and immune " +
	  "to being stunned.\n", victim, TO);

    set_alarm(itof(time), 0.0, "remove_ghoul_stun", victim);
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
    do_ghoul_stun();
}
