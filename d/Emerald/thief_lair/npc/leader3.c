/* /d/Emerald/thief_lair/npc/leader.c
   
   Base file inherited by leaders of the bandit group.
   (/thief_lair/npc/lieutenant.c and
    /thief_lair/npc/telanevar.c)
   Implements functionality which allows the leader to appear to be
   directing nearby bandits in combat.
   Code (c) 1999 Damian Horton. BKA Casimir.
   Protection routines, ideas and assistance provided by Shiva.
*/

#pragma strict_types
#pragma save_binary 

#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <options.h>
#include "/d/Emerald/sys/paths.h"

// Leaders get the thug special attack routine:
inherit THIEF_LAIR_DIR + "/npc/base_thug"; 
                        
// Global variables                    
public int command_mode = 0; //True when he is engaged in directing
                             //a battle.

// Prototypes:

public mixed check_for_protectors();
void command_troops();

void 
create_bandit_leader()
{
    add_prop(OBJ_M_NO_ATTACK, check_for_protectors);
}

void
create_bandit()
{
    create_bandit_leader();
}
/* Returns an array of all the bandits, leaders excepted,
   currently in the room.
*/
  
object*
get_bandits()
{
    object *bandits;
    bandits = filter(all_inventory(environment(this_object())),
		     &->query_bandit());   
    return bandits;
}

/* Returns an array containing all livings who are presently in combat
   with bandits, or bandit leaders.
*/

object*
get_foes()
{
    int i; // loop index
    object *inv, *foes;
    object member; // a member of *inv
    foes = ({}); // return value
    inv = all_inventory(environment(this_object()));
    // everything in the room.

    // Determining who in the room is fighting bandits:
    
    for (i = 0; i < sizeof(inv); i++)
    {
	member = inv[i];
	if (living(member) && ((member->query_attack()->query_bandit()) ||
	    (member->query_attack()->query_bandit_leader())))
	  {
	    // The living is fighting either a bandit, or bandit leader,
	    // mark him as a foe.
	    foes += ({member});
	}
    } 
    
    return foes;
}
/* Instructs all bandits in the chamber to attack a particular foe.
   Called from command_troops, and check_for_protectors.
*/

void
strike_down(object enemy)
{   
    object *bandits;
    object abandit; // Not sure why I need to use this variable. See below:
    int i; // loop index
    bandits = get_bandits();
  
    if (sizeof(bandits))
    {
	command("emote shouts: Slay the " + enemy->query_nonmet_name() + "!");
	for (i = 0; i < sizeof(bandits); i++)
	{
	  /* I dont understand why I cannot use bandits[i]->attack_object(enemy),
	     but this works.
	  */
	    abandit = bandits[i];

	    // The bandits cannot fight in a coordinated manner when blind:

	    if (check_blind(abandit))
	    {
		abandit->command("shout I can't see a thing!");
	    }

	    else
	    {
		enemy->catch_msg(QCTNAME(abandit) + " attacks you!\n");
		tell_room(environment(this_object()), QCTNAME(abandit) +
			  " attacks " + QTNAME(enemy) + "!\n", enemy, 
			  abandit);
		abandit->attack_object(enemy);	    
	    }
	}
    }

    // The leader will engage in combat if there are fewer than four other
    // bandits in the room.

    if (sizeof(bandits) < 4)
    {
	enemy->catch_msg(QCTNAME(this_object()) + " attacks you!\n");
	say(QCTNAME(this_object()) + " attacks " + QTNAME(enemy) + "!\n");
	attack_object(enemy);
    } 
}

/* This function is called when any bandit in the presence of a leader
   is attacked. If the leader is not in command_mode, pushes the leader
   into command_mode.
*/

void
request_orders()
{
    if (!command_mode)
    {
	command_mode = 1;
	command_troops();
    }
    
    return;
}

/* Bandit leaders coordinate all bandits in their cave. Should 
   a battle insue between the bandits and their foes, this
   function allows the leader to instruct the bandits to pick
   on a particular foe (the one with the least defence value).
   This function initiates a recursive loop which will continue
   until the bandits are no longer engaged in combat.
*/   

void
command_troops()
{  
    object *foes;  // Everyone fighting bandits in the room.
    object foe; // A member of foes.
    object weak_foe; // The member of *foes with the lowest defence skill.
    int i;        // loop indices.
    int defence;  // Defence of a foe.
    int low_defence; //Least defence value encountered so far.
   
    foes = get_foes();

/* If no one is fighting bandits in the room then we return 
   from the function and prevent recursion. We also clean
   up the global variables. */

    if (!sizeof(foes))
    {
	command_mode = 0;
	return;
    }
    
    /* The bandits are engaged in combat so we
   call this function again in a minute */

    set_alarm(60.0, 0.0, command_troops);

// leaders cannot function effectivly if blinded:

    if (check_blind(this_object()))
    {
	command("shout What's going on? What's going on?!");
	command("shout Kill 'em! Kill them all!");
	return;
    }
  
// Determing the foe with the least defence.

    low_defence = 100;
    for (i = 0; i < sizeof(foes); i++)
    {
	foe = foes[i];
	defence = foe->query_stat(SS_DEFENCE);
	if (defence < low_defence)
	{
	    low_defence = defence;
	    weak_foe = foe;
	}
    }

// Command troops to attack  the weakest foe.

    strike_down(weak_foe);
}

/* If there are more than 3 bandits in the room, this function will be used
   to set OBJ_M_NO_ATTACK.
*/
 
public mixed
check_for_protectors()
{
    object *bandits; // bandits in the room

    bandits = get_bandits();
    if (command_mode && sizeof(bandits) > 2)
	// 2 or more bandits other than himself are in the chamber
    {
        return "The other bandits swarm you, preventing you from reaching him.\n";
    }

    return 0;
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 * 
 * This function is modified so that the leader will take grave
 * offence when someone makes threatening motions towards. He will
 * order his troops to strike_down() his would-be attacker. He,
 * however, will not engage in combat unless his
 */

public void
attacked_by(object ob)
{
    ::attacked_by(ob); 

/* If the bandits are already engaged in combat, we ignore the
   instructions below this point. */

    // For debugging purposes:
    write("Tevalanar's command mode is: " + command_mode + "\n");
    if (command_mode)
    {
	return;
    }
   
    // Make battle plans:
    command_mode = 1;
    command_troops();

    /* If the leader has sufficient protectors, do not allow him to
       engage in combat. */ 

    if (check_for_protectors())
    {
	write(check_for_protectors());

	/* Since  ::attacked_by() was called, the leader is engaged in combat -
	   Not for long, though. */
	set_alarm(0.0, 0.0, &ob->stop_fight(this_object()));
	set_alarm(0.0, 0.0, &stop_fight(ob));
    }
}

/* Function to identify bandit leaders.
*/

public int
query_bandit_leader()
{
    return 1;
}

/* Leaders do not identify themselves as bandits so that they
   will not be forced to attack when strike_down() is called.
*/
public int
query_bandit()
{
    return 0;
}
































