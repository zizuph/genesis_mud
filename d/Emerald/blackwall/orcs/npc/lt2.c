/* One of the two orcish lieutenants found with Morognor.
   Code (c) 2000 Damian Horton. BKA Casimir. */

#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/orc.c";
inherit "/d/Emerald/lib/aid_npc";

#include <wa_types.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define ORC_DIR "/d/Emerald/blackwall/orcs" 

// special attack prototypes:
int slash(object enemy);
int kick(object enemy);

void
create_orc() 
{
    set_adj("broad");
    add_adj("scar-faced");
    set_short("broad scar-faced orc");
    set_long("Black skinned, and possessed of a brutally scarred face, "+
	     "this orc presents a truly frightenining appearance. He has "+
	     "an unusually broad and powerful build, for an orc and lacks "+
	     "nothing in height, either.\n");
  
    set_skill(SS_2H_COMBAT, 90);

    config_orc(100);
    set_alignment(- 750); 

    set_appearance(50); //ugly as can be   
    add_prop(CONT_I_HEIGHT, 170);
    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(CONT_I_VOLUME, 147000);

    set_act_time(8);
    add_act("emote watches you closely.");
    add_act("emote fondles the hilts of his swords.");
    add_act("emote glares threateningly.");

    set_cact_time(8);
    add_cact("emote utters harsh curses which are, fortunately, beyond "+
	     "your comprehension.");
    add_cact("emote snarls at you with a primal ferocity.");
    add_cact("emote screams angrily!\n");

    set_special_attack_percent(24); //two weapons have their advantages
    add_special_attack(slash, 100, "slash");

    add_equipment(ORC_DIR + "/wep/heavy_broadsword");
    add_equipment(ORC_DIR + "/wep/heavy_broadsword");
    add_equipment(ORC_DIR + "/arm/bs_helmet");
    add_equipment(ORC_DIR + "/arm/chain_greaves");
    add_equipment(ORC_DIR + "/arm/chain_coat");

    set_give_aid(1); //aids npcs who ask for it
    set_exp_factor(125); //specials, high skills
}

/* Modified so that he asks for aid from fellow npcs (orcs).*/
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    get_assistance(ob); //asks for assistance from nearby orcs
}
 
/* sets unarmed combat off, giving more axe attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

/* The lieutenant's damage special.
*/
int
slash(object enemy)
{  
    mixed* hitresult;
    string how, hdesc;
    int sword;

    // Does he possess a sword?

    sword = sizeof(filter(this_object()->query_weapon(-1),
			    &->id("sword"))); 
    
    if (sword == 0){  // For some reason he does not possess a sword, so
                       // he kicks instead.
	return kick(enemy);
    }
    
    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(500)))
    {
	hitresult = enemy->hit_me(300, W_SLASH, this_object(), -1);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg(QCTNAME(this_object()) + " strikes your head "+
			   "solidly with his broadsword!\n\nYou lose "+
			   "consciousness before striking the ground.\n");

	    tell_watcher(QCTNAME(this_object()) + " strikes "+
			 QTNAME(enemy) + " solidly in the head with his "+
			 "broadsword knocking " + enemy->query_pronoun +
			 "to the ground!", enemy);
	    
	    enemy->do_die(this_object());
	}
	else
	{
	    hdesc = "flesh"; //this will be changed to something else, later
	    how = " nicks ";
	    if (hitresult[0] > 10)
	    {
		how = " cuts ";
	    }
	    if (hitresult[0] > 25)
	    {
		how = " strikes ";
	    }
	    if (hitresult[0] > 50)
	    {
		how = " savages ";
	    }
	    
	    enemy->catch_msg(QCTNAME(this_object()) + how +   
			     "you with a powerful swing of a "+
			     "broadsword.\n");
	    tell_watcher(QCTNAME(this_object()) + how + QTNAME(enemy) +
			 " with a powerful swing of a broadsword!\n");
	}
    }

    else //the attacked missed:
    {
	enemy->catch_msg(QCTNAME(this_object()) + " swings wildly at you "+
	    "with a broadsword.\n");
	tell_watcher(QCTNAME(this_object()) + " swings wildly at "+
		     QTNAME(enemy) + ".\n", enemy);
    }
  return 1;
} 

/* Special attack called when the lieutenant is missing his polearm.
*/

int
kick(object enemy)
{  
    mixed* hitresult;
    string how;
    object me = this_object();

    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(500)))
    {
	hitresult = enemy->hit_me(query_stat(SS_STR) + 100, W_BLUDGEON, 
				  this_object() , -1);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg(QCTNAME(this_object()) +
			     " kicks you brutally in the "+
			     "stomach!\n\nYou see spots before your eyes...\n"+
			     QCTNAME(this_object()) + " hits you in the gut "+
			     "aqain!!\nAnd again!!!\nAnd again!!!!\n\nYou "+
			     "pass out...\n\n");
	    
 	    tell_watcher(QCTNAME(this_object()) + " kicks " + 
			 QTNAME(enemy) + " brutally in the stomach!\n"+
			 QCTNAME(this_object()) + " hits " + 
			 enemy->query_objective() + 
			 "in the gut repeatedly until "+
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
			     "in the gut!\n");
	    tell_watcher(QCTNAME(this_object()) + " kicks "+
			 QTNAME(enemy) + how + " in the gut!\n", enemy);
	}
    }
    else
    {
	enemy->catch_msg(QCTNAME(this_object()) + " kicks at you "+
			 "ineffectually.\n");
	tell_watcher(QCTNAME(this_object()) + " kicks at " + 
		 QTNAME(enemy) + "ineffectually.\n", enemy);
    }

    return 0; // Deliberate. The kick is in addition to all normal attacks.
}


