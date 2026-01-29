/*
 * Disarm Foe Unarmed (Dex/Dex/Str)
 *   This skill enables the living to disarm another foe using the
 *   livings weapons.
 *   The success is dependant on:
 *	  +:  The skill level.
 *	      Dex and Str.
 *	  -:  Opponents: Dex and Str, Awareness
 *	      Bad light condition.
 */

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <wa_types.h>
#include "defs.h"

inherit TELL_FILE;

void wield_again(object who);
void get_again(object who);
 
varargs int
disarm_foe_unarmed(object who, object tp)
{
    object *weps, weapon;
    int suc, opp_weapon_skill;

    if(!tp) tp = TP;
    if(!who)
	who = tp->query_attack();
    if(!who)
	return notify_fail("Disarm who?");
    if(!sizeof(weps = who->query_weapon(-1)))
	return notify_fail("But, "+QTNAME(who)+" does not wield any weapon!\n");
    weapon = weps[0];
    opp_weapon_skill = SS_WEP_FIRST + (weapon->query_wt() - W_FIRST);

    suc = tp->resolve_task(DIFF_HARD,
	   ({
	       SS_DIS_FOE_UNARMED,
	       SS_UNARM_COMBAT,
	       SKILL_AVG, TS_DEX, TS_DEX, TS_STR, SKILL_END,
	   }),
	   who,
	   ({
	       opp_weapon_skill,
	       SS_DEFENCE,
	       SKILL_AVG, TS_DEX, TS_DEX, TS_STR, SS_AWARENESS, SKILL_END,
	   }) );
    if (tp->query_name() == "Rogon")
	tp->catch_msg("Success: " + suc + "\n");
    tp->attack_object(who);
    if(suc <= 0) {
	tellem(tp, who,
	    "$You $try to disarm #name, but $fail.\n");
	return 1;
    }
    if(suc < 20) {
	set_this_player(who);
	weapon->unwield_me();
	set_this_player(tp);
	tellem(tp, who, "$You succesfully managed to disarm #name!!\n");
	if (who->query_npc())
/*
            set_alarm(10.0,0.0,&wield_again(who));
*/
      set_alarm(10.0, 0.0, &wield_again(who));
	return 1;
    }
    else {
	tellem(tp, who,
	    "$You successfully disarmed #name! #He #loose the grip of it!\n");
	set_this_player(who);
	weapon->move(ENV(tp));
	set_this_player(tp);
	if(who->query_npc())
/*
            set_alarm(itof(suc/10),0.0,&get_again(who));
*/
      set_alarm(3.0, 0.0, &get_again(who));
	return 1;
    }
}

wield_again(object who)
{
    who->command("wield weapon");
}

get_again(object who)
{
    who->command("get weapons");
    who->command("wield weapon");
}
