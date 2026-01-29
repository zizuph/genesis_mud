/*
 * Disarm Foe Armed (Dex/Dex/Str)
 *   This skill enables the living to disarm another foe using the
 *   livings weapons.
 *   The success is dependant on:
 *	  +:  The skill level.
 *	      Dex and Str.
 *	      The weapons tohit.
 *	  -:  Opponents: Dex and Str, Awareness
 *	      Bad light condition.
 */

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

inherit TELL_FILE;

void wield_again(object who);
void get_again(object who);
 
varargs mixed
disarm_foe_armed(object who, object tp)
{
    object *weps;
    int tohit;
    int suc;
    int i;

    if(!tp) tp = TP;
    if(!who)
	who = tp->query_attack();
    if(!who)
	return notify_fail("Disarm who?");
    if(!sizeof(who->query_weapon(-1)))
	return notify_fail("But, "+HE_SHE(who)+" does not wield any weapon!\n");


    weps = tp->query_weapon(-1);
    if(!sizeof(weps))
	return notify_fail("But you have not a weapon to disarm with.\n");

    for(i=0;i<sizeof(weps);i++)
	if(weps[i]->query_hands()!=W_BOTH)
	    tohit += weps[i]->query_wchit();
	else
	    tohit += weps[i]->query_wchit()*2/3;

    suc = tp->resolve_task(TASK_DIFFICULT,
	   ({
	       SS_DIS_FOE_ARMED,
	       SKILL_AVG, TS_DEX, TS_DEX, TS_STR, SS_AWARENESS, SKILL_END,
	       tohit
	   }),
	   who,
	   ({
	       SKILL_AVG, TS_DEX, TS_DEX, TS_STR, SS_AWARENESS, SKILL_END,
	       SS_DEFENCE
	   }) );
    if(suc <= 0) {
	tellem(tp, who,
	    "$N $try to disarm #n, but $fail.\n");
	return 1;
    }
    if(suc < 50) {
	who->command("unwield weapon");
	tellem(tp, who,
	    "$N succesfully $manage to disarm #n!!\n");
	if(who->query_npc())
      set_alarm(10.0, 0.0, &wield_again(who));
	return 1;
    }
    else {
	tellem(tp, who,
	    "$N successfully $disarm #n, and #he #loose the grip of it!\n");
	who->command("drop weapon");
	if(who->query_npc())
      set_alarm(10.0, 0.0, &get_again(who));
	if(tp->query_npc() || tp->query_name()=="Rogon")
	    tp->command("get weapon");
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
