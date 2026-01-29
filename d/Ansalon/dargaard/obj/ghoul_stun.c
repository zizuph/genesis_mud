/*
Stun attack used by Serion

Idea from dragon fear coded by Erine & Jeremiah.

Coded : 4/97 by Arman
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
    set_name("ghoul_paralyze");

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
      "project"});

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
    write("You are completely paralyzed, and unable to do that.\n");
    return 1;
}


void
remove_dragon_fear(object victim)
{
    object vict = victim; 

    vict->catch_msg("You no longer feel paralyzed.\n");

    tell_room(E(vict), QCTNAME(vict) + " no longer looks paralyzed.\n", vict, TO);

    vict->remove_stun();
    remove_object();
}


void
do_dragon_fear()
{
    int time;

    time = 25 + random(10);

    victim->catch_msg("You feel paralyzed!\n");
    victim->add_stun();

    if(victim->query_wiz_level())
	victim->catch_msg("As a wizard, you are immune to being paralyzed.\n");


    tell_room(E(victim), QCTNAME(victim) + " looks paralyzed!\n", victim, TO);

    if (victim->query_wiz_level())
	tell_room(E(victim), C(PRONOUN(victim)) + " is a wizard and immune " +
	  "to being paralyzed.\n", victim, TO);

    set_alarm(itof(time), 0.0, "remove_dragon_fear", victim);
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
    do_dragon_fear();
}
