
/* File         : /d/Khalakhor/n_speir/clachdun/sword_breaker_shadow.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : October 15th, 1998
 * Purpose      : A Shadow used by my swordbreaker 
 *                (Does the actual breakign attempts)
 * Related Files: /d/Khalakhor/n_speir/clachdun/wep/swordbreaker.c
 * Comments     :
 * Modification :
 */
inherit "/std/shadow";

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include <language.h>

#define DEBUG_WHO   find_player("igneous")

#ifdef DEBUG_WHO
#define DEBUG(x)    DEBUG_WHO->catch_tell(x)
#else
#define DEBUG(x)
#endif

static int Break_chance, Break_task, Break_time = time();
static object SwBreaker;

public void
remove_sword_breaker_shadow()
{
    remove_shadow();
}

public void
add_sword_breaker_shadow(object who, object breaker)
{
    if (!shadow_me(who))
    {
	set_alarm(0.0, 0.0, remove_sword_breaker_shadow);
	return;
    }
    SwBreaker = breaker;
    // Npcs with this are a more skilled than players
    if (who->query_npc() || who->query_wiz_level())
    {
	Break_task = TASK_ROUTINE;
	Break_chance = 5;
    }
    else
    {
	Break_task = TASK_DIFFICULT - (who->query_skill(SS_PARRY) * 2);
	Break_chance = 30 - (who->query_skill(SS_WEP_KNIFE) / 5);
    }
}

public int
query_not_attack_me(object who, int aid)
{
    int amount, task_result, result;
    object weapon;
    string how;

    // If something else blocked the attack then we do nothing
    if (result = shadow_who->query_not_attack_me(who, aid))
	return result;

    if (!random(Break_chance))
    {
	// A timestamp to make sure if we are fighting multiple enemies
	// We don't dammage them all in a combat round or 2
	if (time() < Break_time + Break_chance)
	    return 0;

	// See if we are being hit with a edged weapon
	if (!objectp(weapon = who->query_weapon(aid)) ||
	  (weapon->query_wt() != W_SWORD && weapon->query_wt() != W_KNIFE))
	    return 0;

	// Dblcheck to make sure the weapon is still wielded
	if (SwBreaker->query_wielded() != shadow_who)
	{
	    set_alarm(0.0,0.0,remove_sword_breaker_shadow);
	    return 0;
	}
	Break_time = time();
	if (task_result = shadow_who->resovle_task(Break_task, ({SKILL_AVG, 
	      TS_DEX, TS_WIS, SKILL_END, SS_PARRY}), who, ({SKILL_AVG, 
	      TS_INT, TS_WIS, SKILL_END, SS_PARRY})) >= 0)
	{
	    // Success!!
	    result = 1;

	    // A chance to break the weapon entirely!!
	    if (!random(Break_chance) && 
	      !weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	    {
		shadow_who->catch_tell("You manage to catch "+
		  LANG_POSS(who->query_the_name(shadow_who)) + " " +
		  weapon->short()+" with your "+SwBreaker->short()+
		  " snapping the "+LANG_POSS(weapon->short())+" "+
		  "blade with a clever counter parry.\n");
		who->catch_tell(shadow_who->query_The_name(who) +
		  " manages to catch your "+weapon->short()+" with "+
		  HIS_HER(shadow_who)+" "+SwBreaker->short()+", snapping "+
		  "the blade of your "+weapon->short()+" with a "+
		  "clever counter parry.\n");

		DEBUG(shadow_who->query_name() +" snapped "+
		  LANG_POSS(who->query_name())+" "+weapon->short()+".\n");

		weapon->remove_broken(1);
	    }
	    else
	    {
		amount = random(2) + 1;
		//  Magical weapons are harder to damage
		if (weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
		    amount -= 1;
		switch(amount)
		{
		case 0:   how = "undamaged";   break;
		case 1:   how = "slightly damaged";   break;
		case 2:   how = "damaged";     break;
		default:  how = "ruined";      break;
		}

		shadow_who->catch_tell("You deftly catch "+
		  LANG_POSS(who->query_the_name(shadow_who))+" "+
		  weapon->short()+" with your "+SwBreaker->short()+
		  ", leaving the "+weapon->short()+" " + how + 
		  " by your twisting parry.\n");
		who->catch_tell(shadow_who->query_The_name(who)+" manages to "+
		  "catch your "+weapon->short()+" with "+HIS_HER(shadow_who)+
		  " "+SwBreaker->short()+" with a skillfully parry, leaving "+
		  "your "+weapon->short()+" "+how+" by the quick twist of "+
		  HIS_HER(shadow_who)+" "+SwBreaker->short()+".\n");
		shadow_who->tell_watcher(QCTNAME(shadow_who)+ " manages to "+
		  "catch "+LANG_POSS(QTNAME(who))+" "+weapon->short()+
		  "with a skillful parry of "+HIS_HER(shadow_who)+ " "+
		  SwBreaker->short()+", leaving the "+weapon->short()+" "+how+
		  "from the encounter.\n", who);
		if (amount)
		    weapon->set_dull(weapon->query_dull() + amount);
	    }
	}
	else
	{
	    // Failure :(
	    result = 0;
	    if (!shadow_who->query_option(OPT_GAG_MISSES))
		shadow_who->catch_tell("You attempt to damage "+
		  LANG_POSS(who->query_the_name(shadow_who))+" "+ 
		  weapon->short() +" with a twisting parry of "+
		  "your "+SwBreaker->short()+", but fail.\n");
	    if (!who->query_option(OPT_GAG_MISSES))
		who->catch_tell(shadow_who->query_the_name(who) +
		  " attempts to entangle your "+weapon->short()+
		  " in "+HIS_HER(shadow_who)+" " +SwBreaker->short()+
		  ", but fails to do so.\n");
	    shadow_who->tell_watcher_miss(QCTNAME(shadow_who) +" attempts "+
	      "to entangle "+LANG_POSS(QTNAME(who))+" "+weapon->short()+
	      " with "+HIS_HER(shadow_who) +" "+ SwBreaker->short()+
	      ", but fails to do so.\n", who);
	}
	DEBUG("Task result by "+shadow_who->query_name()+" on "+who->query_name()+
	  " was:   "+task_result+".\n");

    }
    return result;
}

void
query_sword_breaker_vars()
{
    DEBUG("Frequency :"+ Break_chance+"\n");
    DEBUG("Task  : "+ Break_task +"\n");
    DEBUG("Time : "+ Break_time + "\n");
}
