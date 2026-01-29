/*
 *  Shield bash.
 *
 *  An skill which makes you able to bash your opponent using your shield.
 *
 *  +:
 *     Bash skill (Att)
 *     The shields armour class. (Att)
 *     Strength (Att)
 *     Dexterity (Att)
 *  -: The weight of the worn shield (Att)
 *     Defence skill (Def)
 *     Dexterity (Def)
 *     The armour class (Def) (Intrinsic because of hit_me.)
 */

#include <ss_types.h>
#include <wa_types.h>
#include <comb_mag.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

#define PROC_HURT did_hurt[0]
#define HIT_DESC  did_hurt[1]
#define PROC_HIT  did_hurt[2]
#define DAMAGE	  did_hurt[3]

inherit TELL_FILE;

int
is_shield(object arm)
{
    return arm->query_at()==A_SHIELD;
}

int
weight_formula(object tp, int weight)
{
    int normal_weight;

    normal_weight = STR(TP)*200 + 500;

    if(weight >= normal_weight)
	return (weight-normal_weight)/500;
    else
	return 0;
}


varargs int
bash(object who, object tp)
{
    object *armours;
    object *shields;
    object shield;

    int suc;
    mixed *did_hurt;

    string desc_shield;
    string how;

    if (!tp) tp = TP;
    if (!who)
	who = tp->query_attack();
    if (!who || !living(who))
	return notify_fail("Bash who?\n");

    armours = tp->query_armour(-1);

    shields = filter(armours, "is_shield", TO);

    if (!sizeof(shields))
	return notify_fail("You can't when you do not wear a shield!\n");

    shield = shields[0];

    suc =(tp->query_skill(SS_BASH) + tp->query_skill(SS_DEFENCE) +
	  (tp->query_stat(SS_DEX) + tp->query_stat(SS_STR)*2)/3) +	   
	-(weight_formula(tp, shield->query_prop(OBJ_I_WEIGHT)) +
	  who->query_skill(SS_DEFENCE) + who->query_stat(SS_DEX));

    if (suc < 0)
	suc = 0;

    if (!CAN_SEE(tp, who))
	suc = tp->query_skill(SS_BLIND_COMBAT)*suc/100;

    if (tp->query_name() == "Rogon")
	write("Success: " + suc + "\n");

    did_hurt = who->hit_me(suc, W_BLUDGEON, tp, -1);

    desc_shield = shield->short();

    switch(PROC_HURT) /* ProcHit is actually random(wcpen) */
    {
    case -1:
	how = "$You swing $your "+desc_shield+" against the "+HIT_DESC
	    + " of #name, but miss. ";
	break;
    case 0:
	how = "$You $bash $your "+desc_shield+" into #name's "+HIT_DESC
	    + ", but it bounces off. ";
	break;
    case 1..10:
	how = "$You $manage to hit #name's " + HIT_DESC + " with $your " + 
	     desc_shield + ". ";
	break;
    case 11..20:
	how = "$You $attack #name with $your "+desc_shield+"! It hits #him hard in "
	     + "#name's "+HIT_DESC+". ";
	break;
    case 21..30:
	how =  "$You $deliver a shattering blow with $your "+desc_shield
	     + " which hits #name's "+HIT_DESC+". ";
	break;
    case 31..50:
	how = "$You $smash #name's "+HIT_DESC+" with $your "
	     + desc_shield+", with a crushing sound. ";
	break;
    case 51..70:
	how = "$You $perform a shattering shield bash against #name with $your "+desc_shield+"!";
	break;
    case 71..90:
	how = "$You $amaze #name as $he painfully $crush #name's " + HIT_DESC +
	     " with $your " + desc_shield + ". ";
	break;
    default:
	how = "$You $masssacre #name and #he #scream out in agony "+
	    "as $he $hit #his "+HIT_DESC+" severely! ";
    }

    tellem(tp, who, how + "\n");
    return 1;
}
