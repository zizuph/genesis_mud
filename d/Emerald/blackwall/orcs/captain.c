/* An orcish captain. Found in the orc holy area.

   Code (c) 2000  Damian Horton. BKA Casimir. */

#pragma strict_types
#pragma save_binary 

#include <wa_types.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#define ORC_DIR "/d/Emerald/blackwall/orcs/"

inherit "/lib/unique"; // his weapon is 'unique'
inherit "/d/Emerald/std/orc";
inherit "/d/Emerald/lib/assist"; //he assists other orcs, and will 
                                 //assist other orcs

//prototypes
int shield_charge(object enemy);
int hack(object enemy);
int kick(object enemy);

void
create_orc () 
{
    object axe; // his weapon

    set_adj("threatening");
    add_adj("muscular");
    set_short("threatening muscular orc");
    set_long("This is one mean looking orc. He is huge, towering over "+
	     "most other orcs. His skin is coal black, but unusually "+
	     "unblemished. The gaze of his blood-red eyes seems to "+
	     "devour all things it is set upon.\n");
  
    set_stats(({135 + random(15), 110 + random(15), 140 + random(15),
		  95 + random(15) , 95 + random(15), 125 + random(15)}));
    
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 80);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_AWARENESS, 65);
    set_skill(SS_BLIND_COMBAT, 60);
    set_alignment(- 1000); 

    set_appearance(40);   
    add_prop(CONT_I_HEIGHT, 215);
    add_prop(CONT_I_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME, 135000);

    set_act_time(6);
    add_act("emote sternly commands an orc. The orc appears to obey "+
	    "unquestioningly.");
    add_act("emote 's blood red-eyes stare menacingly at you. It "+
	    "would seem that he wants you to complete whatever "+
	    "business you may have here.");
    add_act("emote broods.");

    set_cact_time(6);
    add_cact("emote speaks harshly in the orcish tongue. You have"+
	     "reason to believe it was some terrible curse directed at "+
	     "elves.");
    add_cact("emote stares threateningly at you, in defiance.\n");
    add_cact("emote screams angrily!");

    set_give_aid(1); // aids npcs who ask for aid
    set_special_attack_percent(20);
    add_special_attack(hack, 75, "hack");
    add_special_attack(shield_charge, 25, "shield_charge");

    axe = clone_unique(ORC_DIR + "/wep/savage_axe", 5,
		       ORC_DIR + "wep/hb_axe");
    axe->move(this_object());
    add_equipment(ORC_DIR + "/arm/chief_breastplate");
    add_equipment(ORC_DIR + "/arm/chief_helm");
    add_equipment(ORC_DIR + "/arm/chief_greaves");
    add_equipment(ORC_DIR + "/arm/chief_gauntlets");
    add_equipment(ORC_DIR + "/arm/chief_shield");

    setuid();
    seteuid(getuid());

    set_exp_factor(150); //dangerous specials, unbalanced stats, good eq
} 

/* sets unarmed combat off, giving more axe attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

/* Done chiefly to prevent players from doing in, special, leave
   tactics against him:
*/
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    // alarmed so that the messages will be printed after the room
    // description, etc.
    get_assistance(ob); //ask for assistance from nearby orcs
    set_alarm(0.0, 0.0, &shield_charge(ob));
	      //charge the player who attacked him
}

/* Modified so that he shield_charges when he assists */
void 
assist_npc(object enemy)
{
    ::assist_npc(enemy);
    set_alarm(0.0, 0.0, &shield_charge(enemy)); //charge that enemy
}

/* A special attack causing considerable damage, AND stunning its victim.
   Morognor requires a shield to be able to perform it, however. Otherwise,
   he will kick() instead.
*/
int
shield_charge(object enemy)
{  
    mixed* hitresult;
    string how;
    int shield;
    object stun; // Morognor stun object passed to victims

    // Does he possess a shield?

    shield = sizeof(filter(this_object()->query_armour(-1),&->id("shield"))); 
    if (shield == 0){  // Doesn't possess a shield therefor kicks instead.
	return kick(enemy);
    }

    if ((enemy->query_stat(SS_DIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(500)))
    {
	hitresult = enemy->hit_me(200, W_BLUDGEON, this_object() , -1);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg(QCTNAME(this_object()) + 
			     " places his shield in "+
			     "front of his "+
			     "body then charges into you, crushing you "+
			     "against a wall! Spasms of agony flare from "+
			     "your crushed ribcage as a terrifying darkness "+
			     "engulfs you!\n");
	    
 	    tell_watcher(QCTNAME(this_object()) +  
			 " places his shield in front of his "+
			 "body then charges into " + QTNAME(enemy)+ ", "+
			 "crushing " + enemy->query_objective() +
			 " against the wall!\n" + 
			 capitalize(enemy->query_pronoun()) + " falls to "+
			 "the ground in a bloodied, lifeless heap.\n",
			 enemy);
	    enemy->do_die(this_object());
	  }

	else
	{
	      how = ({ "dazed",
		       "winded", 
		       "crushed",
		       "pulverized" })[min(3, hitresult[0] / 20)];
	    
	      enemy->catch_msg(QCTNAME(this_object()) +
			       " places his shield in front of his body "+
			       "and then charges into you!\n"+
			       "You are " + how +"!\n");
	      tell_watcher(QCTNAME(this_object()) + 
			   " places his shield in front of "+
			   "his body, and then charges into "
			   + QTNAME(enemy)+
			   "!\n" + capitalize(enemy->query_pronoun()) + 
			   " is " + how + "!\n", enemy);

	      // Enemy is stunned:

	      stun = clone_object(ORC_DIR + "/obj/morognor_stun");
	      stun->set_remove_time(10 + (hitresult[0] / 10));
	      stun->move(enemy);
	      enemy->add_attack_delay(10 + (hitresult[0] / 10), 0);
	}
    }
    
    // attack missed:
    else
    {
	enemy->catch_msg("You step aside as the " + QTNAME(this_object()) +
			 " lowers his shield, and then charges past you!\n");
	tell_watcher(QCTNAME(enemy) + "steps aside as the " + 
		     QTNAME(this_object()) + " lowers his shield and then "+
		     "charges right past " + enemy->query_pronoun() + "!\n",
		     enemy);
    }
  
    return 1;
}

/* A special attack causing lots of damage. Morognor must possess his axe to 
   perform this manoever, otherwise, he will kick(), instead.
*/

int
hack (object enemy)
{  
    mixed* hitresult;
    string how;
    int var1;
    
//  Does he wield an axe with which to hack?

    var1 = sizeof(filter(this_object()->query_weapon(-1),&->id("axe")));
  
    if (var1 == 0) // He does not wield an axe...
    {
	return kick(enemy);
    }

    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(500)))
    {
	hitresult = enemy->hit_me(500, W_SLASH, this_object(), -1);
	if (enemy->query_hp() <= 0)
	{
	    // the player took lethal damage:
	    enemy->catch_msg(QCTNAME(this_object()) + 
			     " brings his axe crashing down upon "+
			     "your forehead, splitting your skull!!!\n\n"+
			     "Death is, mercifully, near instantaneous.\n");  
 	    tell_watcher(QCTNAME(this_object()) + " bring his axe crashing "+
			 "down upon " + QTNAME(enemy) + "'s  forehead, "+
			 "splitting " + enemy->query_possesive() +
			 " skull!!!\n", enemy);
	    enemy->do_die(this_object());
	}
	
	else
	{
	    how = ", barely touching";
   
	    if (hitresult[0] > 10)
	    {
		how = ", slicing into";
	    }

	    if (hitresult[0] > 25)
	    {
		how = ", cutting deeply through";
	    }
	    
	    if (hitresult[0] > 50) 
	    {
		how = ", massacring";
	    }
	
	    enemy->catch_msg(QCTNAME(this_object()) + " hacks at you"+
			     how + " your flesh!\n");
	    tell_watcher(QCTNAME(this_object()) + " hacks at " +
			 QTNAME(enemy) + " " + how + " " + 
			 enemy->query_possessive() + " flesh.\n", enemy);
	    
	}
    }
	// Attack missed:
    else
    {
	enemy->catch_msg(QCTNAME(this_object()) + " futilly hacks at you!\n");
	tell_watcher(QCTNAME(this_object()) + " futilly hacks at "+
		     QTNAME(enemy) + "!\n", enemy);	
    }
  return 1;
} 

/* This is the default special attack for Morognor, and is called only if he
   has somehow managed to misplace either his axe, or his shield. Its not
   as effective as hack or shield_charge, but it occurs IN ADDITION to his
   normal attacks for the round.
*/

int
kick(object enemy)
{  
    mixed* hitresult;
    string how;

    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(500)))
    {
	hitresult = enemy->hit_me(query_stat(SS_STR) + 100, W_BLUDGEON, 
				  this_object() , -1);
	
	if (enemy->query_hp() <= 0)
	{
	    // player  took lethal damage
	    enemy->catch_msg(QCTNAME(this_object()) +
			     " kicks you brutally in the stomach!\n\n"+
			     "You see spots before your eyes...\n"+
			     QCTNAME(this_object()) + " hits you in the gut "+
			     "aqain!!\nAnd again!!!\nAnd again!!!!\n\nYou "+
			     "pass out...\n\n");
	    
 	    tell_watcher(QCTNAME(this_object()) + " kicks " + 
			 QTNAME(enemy) + " brutally in the stomach!\n"+
			 QCTNAME(this_object()) + " hits " + 
			 enemy->query_objective()  + 
			 " in the gut repeatedly until "+
			 "the " + enemy->query_pronoun() +
			 " passes out...\n", enemy);
	    enemy->do_die(this_object());
	}

	else
	{
	    how = ({ "painfully",
			 "damagingly", 
			 "brutally",
			 "crushingly" })[min(3, hitresult[0] / 20)];

	    
	    enemy->catch_msg(QCTNAME(this_object()) + " kicks you " + how +
			     " in the gut!\n");
	    tell_watcher(QCTNAME(this_object()) + " kicks "+
			 QTNAME(enemy) + " " + how + " in the gut!\n", enemy);
	}
    }

    else
    {
	// the attack missed
	enemy->catch_msg(QCTNAME(this_object()) + 
			 " kicks at you ineffectually.\n");
	tell_watcher(QCTNAME(this_object()) + " kicks at " + 
		     QTNAME(enemy) + "ineffectually.\n", enemy);
    }

    return 0; // Deliberate. The kick is in addition to all normal attacks.
}







