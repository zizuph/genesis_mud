/*
 *  Fist Punch.
 *
 *  An unarmed skill which makes you able to punch your opponent.
 *
 *  +: Unarmed skill (Att)
 *     Punching skill (Att)
 *     The gloves armour class. (Att)
 *     Strength (Att)
 *     Dexterity (Att)
 *  -: The weight of the wielded weapon (Att)
 *     Defence skill (Def)
 *     Dexterity (Def)
 *     The armour class (Def) (Intrinsic because of hit_me.
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
protects_arm(object arm, int right)
{
    return member_array(right?TS_RARM:TS_LARM, arm->query_protects()) >=0;
}

int
is_shield(object arm, int right)
{
    return arm->query_at()==A_SHIELD &&
	   member_array(right?TS_RWEAPON:TS_LWEAPON, arm->query_slots()) >=0;
}

varargs int
fist_punch(object who, object tp, int att_id = W_RIGHT)
{
    object wep;
    object glove;

    object *armours;
    object *shields;

    int suc;
    int drawback;

    mixed *did_hurt;

    string desc_hit;
    string desc_arm;
    string how;

    if (!tp)  
	tp = TP;

    if (!who)
	who = tp->query_attack();
    if (!who) 
	return notify_fail("Punch who?\n");

    if (att_id != W_RIGHT && att_id != W_LEFT)
	return notify_fail("You must punch with your fists!\n");

    if (att_id == W_RIGHT) {
	wep   = tp->query_weapon(W_RIGHT);
	glove = tp->query_armour(A_R_ARM);
    } else if (att_id==W_LEFT) {
	wep   = tp->query_weapon(W_LEFT);
	glove = tp->query_armour(A_L_ARM);
    }

    armours = tp->query_armour(-1);

    armours = filter(armours, "protects_arm", TO, att_id == W_RIGHT);
    shields = filter(armours, "is_shield", TO, att_id == W_RIGHT);

    if (sizeof(shields))
	return notify_fail("You can't when you wield a shield on that arm!\n");

    if (wep)
	drawback = wep->query_prop(OBJ_I_WEIGHT)/10;

    suc = tp->query_skill(SS_PUNCH) +
	  tp->query_skill(SS_UNARM_COMBAT)+
	  tp->query_stat(SS_DEX)/2 +
	  tp->query_stat(SS_STR)/2 -
	  who->query_stat(SS_DEX) -
	  who->query_skill(SS_DEFENCE) -
	  drawback;
    
    if (glove)
	suc += glove->query_ac();
    
    suc /= 3;

    suc = suc/2 + random(suc/2);

    if (suc > 100)
	suc = 100;

    did_hurt = who->hit_me(suc, W_BLUDGEON, tp, att_id);

    desc_arm = (att_id == W_RIGHT ? "right arm": "left arm");

    switch(HIT_DESC) {
	case "body":
	    desc_hit = ({"belly", "stomach", "ribs", "solar plexus"})[random(4)];
	    break;
	case "head":
	    desc_hit = ({"chin", "cheek", "nose", "throat"})[random(4)];
	    break;
	case "left arm":
	    desc_hit = "left "+ ({"elbow", "forearm", "shoulder", "hand"})[random(4)];
	    break;
	case "right arm":
	    desc_hit = "right "+ ({"elbow", "forearm", "shoulder", "hand"})[random(4)];
	    break;
	case "left foot":
	    desc_hit = "left "+({"knee","thigh","foot"})[random(3)];
	    break;
	case "right foot":
	    desc_hit = "right "+({"knee","thigh","foot"})[random(3)];
	    break;
	default:
	    desc_hit = HIT_DESC;
    }

    switch(PROC_HIT) /* ProcHit is actually random(wcpen) */
    {
	case -1..0:
	    how = "$You $swing $your "+desc_arm+" towards #n's " + desc_hit + 
		 ", but miss.\n";
	    break;
	case 1..10:
	    how = "$You $punch $your "+desc_arm+" into #n's " + desc_hit +
		  ", and #he #get hurt.\n";
	    break;
	case 11..20:
	    how = "$You $punch a good blow with $your "+desc_arm+
		  " into #n's "+desc_hit+".\n";
	    break;
	case 21..30:
	    how = "$You $punch a shattering blow with $your "+desc_arm+
		 " which hits #n's "+desc_hit+".\n";
	    break;
	case 31..50:
	    how = "$You $smash #n with $your "+desc_arm+" hitting #his "+
		  desc_hit+".\n";
	    break;
	case 51..70:
	    how = "$You $swing $your "+desc_arm+" powerfully into #n's "+
		  desc_hit+".\n";
	    break;
	case 71..90:
	    how = "$You $swing $your "+desc_arm+" striking #n's "+desc_hit+
		  " with awesome power!\n";
	    break;
	case 91..99:
	    how = "$You $deliver a shattering blow with $your "+
		  desc_arm + " which hits #n's " + desc_hit+"!!\n";
	default:
	    how = "In a devastating rage and obscene power, $n's "+desc_arm+
		  " smashes #n's "+desc_hit+" with a bone crushing sound!!\n";
    }

    tellem(tp, who, how);
    if (HP(who)<=0)
    {
	tp->catch_msg(
	    "Your brutal crush fell upon "+QTNAME(who)+" with a shattering force, "+
	    "leaving a barely recognizable corpse at your feet.\n");
	who->catch_msg(
	    QCTNAME(tp)+"'s brutal crush fell upon you with shattering force.\n"+
	    "You see red, black, then nothing..\n");
	tell_room(ENV(tp),
	    QCTNAME(tp)+"'s brutal crush fell upon "+QTNAME(who)+" with shattering force, "+
	    "leaving a barely recognizable corpse at "+HIS_HER(who)+" feet.\n", ({tp, who}));
	who->do_die(tp);
    }
    return 1;
}
