/* One of the two orcish lieutenants found with Morognor.
   Code (c) 2000 Damian Horton. BKA Casimir. */

#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/std/orc.c";
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
    set_adj("towering");
    add_adj("vigilant");
    set_short("towering vigilant orc");
    set_long("Black skinned, and possessed of a face which suggests "+
	     "cruelty, this orc towers over most of his kin. Inspite of "+
	     "his height, he lacks nothing in terms of muscle and size "+
	     "and brandishes his weapon with a frightening confidence.\n");
  
    config_orc(100);
    set_alignment(- 750); 

    set_appearance(35);   
    add_prop(CONT_I_HEIGHT, 220);
    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(CONT_I_VOLUME, 125000);

    set_act_time(6);
    add_act("emote watches you closely.");
    add_act("emote grasps the haft of his serrated halberd "+
	    "confidently while regarding you with a stern stare.");

    set_cact_time(6);
    add_cact("emote utters harsh curses which are, fortunately, beyond "+
	     "your comprehension.");
    add_cact("emote snarls at you with a primal ferocity.");
    add_cact("emote screams angrily!\n");

    set_give_aid(1); //aids npcs who ask for it
    set_special_attack_percent(16);
    add_special_attack(slash, 100, "slash");

    add_equipment(ORC_DIR + "/wep/ser_halberd");
    add_equipment(ORC_DIR + "/arm/bs_helmet");
    add_equipment(ORC_DIR + "/arm/chain_greaves");
    add_equipment(ORC_DIR + "/arm/chain_coat");

    set_exp_value(125); //specials, high skills
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
    int polearm;

    // Does he possess his halberd?

    polearm = sizeof(filter(this_object()->query_weapon(-1),
			    &->id("halberd"))); 
    
    if (polearm == 0){  // Doesn't possess his halberd, therefor 
                       // kicks instead.
	return kick(enemy);
    } 

    if ((enemy->query_stat(SS_WIS) + enemy->query_skill(SS_DEFENCE)) < 
	(query_stat(SS_DIS) + random(500)))
    {
	hitresult = enemy->hit_me(350, W_SLASH, this_object(), -1);
	
	if (enemy->query_hp() <= 0)
	{
	    enemy->catch_msg("A vicious slice from , " +
			     QTNAME(this_object()) +
			     "'s halberd tears open your belly! "+
			     "A horrible agony engulfs you as blood "+
			     "and internal organs begin to seep from "+
			     "the wound. The pain is too horrible "+
			     "to bear and the orc mercifully ends "+
			     "your life.\n");
	    
	    tell_watcher("A vicious slice from " + QTNAME(this_object()) +
			 "'s halberd tears open " + QTNAME(enemy) +
			 "'s belly!\n", enemy);
	    
	    enemy->do_die(this_object());
	}
	else
	{
	    hdesc = "flesh"; //this will be changed to something else, later
	    how = " nicks ";
	    if (hitresult[0] > 10)
	    {
		how = " slices into ";
	    }

	    if (hitresult[0] > 25)
	    {
		how = " tears open ";
	    }
	    if (hitresult[0] > 50)
	    {
		how = " ravages ";
	    }
	    
	    enemy->catch_msg(QCTNAME(this_object()) + how + " your "+
			     hdesc + " with his savage halberd.\n");
	    tell_watcher(QCTNAME(this_object()) + how + QTNAME(enemy) +
			 "'s " + hdesc + QTNAME(enemy) + how + 
			 enemy->query_possessive() + " flesh.\n", enemy);
	     
	}
    }

    else //the attacked missed:
    {
	enemy->catch_msg(QCTNAME(this_object()) + " swings wildly at you "+
	    "with his halberd.\n");
	tell_watcher(QCTNAME(this_object()) + "  swings wildly at "+
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

