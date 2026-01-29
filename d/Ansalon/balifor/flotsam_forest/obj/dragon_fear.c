/*
dragon_fear.c
-------------

Idea from 'fear.c' coded by Erine.

Coded ........: 95/03/29
By ...........: Jeremiah

Latest update : 98/05/17
By Arman, a check whether player race is kender or not.

*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

public int no_command();

int time;   /* The duration the dragon fear last in a player. Depends on */
/* players wisdom and discipline.                            */

object victim;


create_object() 
{
    seteuid(getuid());
    set_name("Dragon_fear");

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
      "project","charge","kattack","plexus","axekick","brawl","roundhouse","maegeri",
      "swarm","smash"});

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
    write("You are paralyzed by dragon fear.\n");
    return 1;
}


void
remove_dragon_fear(object victim)
{
    object vict = victim; 

    vict->catch_msg("Your fear eases. You think you have shaken off " + 
      "the dragon fear, and are able to move again.\n");

    tell_room(E(vict), QCTNAME(vict) + " seems to have shaken off " + 
      "the dragon fear, and is able to move again.\n", vict, 
      TO); 

    remove_object();
}


void
do_dragon_fear()
{
    int time;   /* The duration the dragon fear last in a player. */
    /* Depends on the players wisdom and discipline.  */

    time = 80 - (victim->query_base_stat(SS_WIS) / 20) *
    (victim->query_base_stat(SS_DIS) / 10);

    if(time < 10)
	time = 0;


    if (victim->query_knight_level() == 5 || (victim->query_knight_level() == 4 &&
	victim->query_knight_sublevel() > 5))
    {
	victim->catch_msg("Terror sweeps over you, threatening to overcome you "+
	  "fully. Gritting your teeth, you fight the fear back, keeping "+
	  "control of yourself.\n");
	tell_room(E(victim), QCTNAME(victim)+" grits "+POSSESSIVE(victim)+" teeth as "+
	  "the dragonfear sweeps over "+OBJECTIVE(victim)+", but "+PRONOUN(victim)+
	  " manages to keep control of "+OBJECTIVE(victim)+"self.\n", victim, TO);
	remove_object();
	return;
    }

    if(victim->query_race_name() == "kender")
    {
	victim->catch_msg("You can barely contain your excitement " +
	  "as you find yourself face to face with a real dragon!\n");
	tell_room(E(victim),QCTNAME(victim) + "'s face lights up " +
	  "with excitement as " +HE(victim)+ " finds " +
	  HIM(victim)+ "self face to face with a real dragon!\n", victim, TO);
	remove_object();
	return;
    }

    if(!time)
    {
	victim->catch_msg("You feel a slight chill by the presence of a " +
	  "dragon. Very impressive animals, but you're " +
	  "too experienced to be really intimidated.\n");

	tell_room(E(victim), QCTNAME(victim) + " shivers slightly.\n", 
	  victim, TO);

	remove_object();
	return;
    }

    victim->catch_msg("You are suddenly overcome by a tremendous " +
      "terror. Your face turns pale. The blood in your " +
      "veins run cold. You feel you are unable to move, " +
      "paralyzed by dragon fear.\n");

    if(victim->query_wiz_level())
	victim->catch_msg("You are a wizard and immune to dragon fear.\n");


    tell_room(E(victim), "Suddenly " + QCTNAME(victim) + " stiffens. " +
      C(POSSESSIVE(victim)) + " face turns pale and " + 
      POSSESSIVE(victim) + " eyes widen. " + C(PRONOUN(victim)) +
      " seems to be paralyzed by dragon fear.\n", victim, TO);

    if (victim->query_wiz_level())
	tell_room(E(victim), C(PRONOUN(victim)) + " is a wizard and immune " +
	  "to dragon fear.\n", victim, TO);

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
