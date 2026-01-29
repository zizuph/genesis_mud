/*
    Created by Milan.
    This file is to be inherited in dragonarmy_soul.c
    It provides functionality for offensive dragonarmy special
    Function dattack(string str) should be executed when player issues command

    Following functions could be masked in division specific souls in order
    to customize behaviour of dattack(). Default behaviour is that of blue
    army special slash. Only dattack_message() needs to be masked always.
    For explanation see below.

int query_dattack_damage_type()
float query_dattack_prepare_time(object tp)
float query_dattack_relax_time(object tp)
int query_dattack_weapon_aid(object tp, object weapon)
int query_dattack_weapon_hit(object tp, object weapon)
int query_dattack_weapon_pen(object tp, object weapon)
int query_dattack_skill(object tp)

void dattack_do_die(object tp, object target)
void dattack_message(object tp, object target,
		string weapon, int weapon_type,
		int phurt, string hitloc, int phit, int dam)

object choose_dattack_weapon(object tp)
*/
#pragma strict_types
#pragma save_binary
#pragma no_clone

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "../guild.h"

#define DATTACK_PROP "_dragonarmy_dattack_prop"

/*** Prototypes ****************************************************/
varargs object get_one_target_from_string(string str, string verb = "attack", int friendly = 0);
mixed cannot_attack_target(object tp, object ob, string attack);
/*******************************************************************/

/*
 * Function name: query_dattack_damage_type
 * Returns:       int - damage type of our special attack
 */
int
query_dattack_damage_type()
{
    return W_SLASH;
}

/*
 * Function name: query_dattack_prepare_time
 * Arguments:     object tp	- who does special attack
 * Returns:       float - time between command and actual attack
 */
float
query_dattack_prepare_time(object tp)
{
    float delay;
    delay = tp->query_speed(3+random(10));
    return delay;
}

/*
 * Function name: query_dattack_relax_time
 * Arguments:     object tp	- who does special attack
 * Returns:       float - time to wait after attack before new can be started
 */
float
query_dattack_relax_time(object tp)
{
    float delay;
    delay = tp->query_speed(3+random(10));
    return delay;
}

/*
 * Function name: query_dattack_weapon_aid
 * Arguments:     object tp	- who does special attack
 *		  object weapon - weapon used for special attack
 * Returns:       int - The hand(s) this weapon is used with
 * Remark:        This function should work fine when 'weapon' is wielded
 *                weapon or worn armour. 
 */
int
query_dattack_weapon_aid(object tp, object weapon)
{
    int i, aid = 0, *slots = weapon->query_slots();

    for(i=0; i<sizeof(slots); i++)
	aid += slots[i];

    return aid;
}

/*
 * Function name: query_dattack_weapon_hit
 * Arguments:     object tp	- who does special attack
 *		  object weapon - weapon used for special attack
 * Returns:       int - hit value special attack is performed with
 */
int
query_dattack_weapon_hit(object tp, object weapon)
{
    return weapon->query_hit()*2;
}

/*
 * Function name: query_dattack_weapon_pen
 * Arguments:     object tp	- who does special attack
 *		  object weapon - weapon used for special attack
 * Returns:       int - pen value special attack is performed with
 */
int
query_dattack_weapon_pen(object tp, object weapon)
{
    int pen = tp->query_stat(SS_STR) /2;
    pen += tp->query_stat(SS_DEX) /2;
    pen += tp->query_stat(SS_INT) /5;
    pen /= 3;
    pen += weapon->query_pen() /2;
    return pen;
}

/*
 * Function name: query_dattack_skill
 * Arguments:     object tp	- who does special attack
 * Returns:       int - how skilled is for special attack
 */
int
query_dattack_skill(object tp)
{
    return tp->query_skill(SS_DRAGONARMY_ATTACK);
}

/*
 * Function name: dattack_do_die
 * Description:   This function should be masked if we want to do special
 *		  things when we give killing blow (e.g. dismember, pulp)
 *		  Do not forget to call target->do_die(tp); when masking!
 * Arguments:     object tp	- killer
 *		  object target - poor target
 */
void
dattack_do_die(object tp, object target)
{
    target->do_die(tp);
}

/*
 * Function name: dattack_message
 * Description:   Displays all appropriate messages about our special attack
 * Arguments:     object tp	- attacker that used special attack
 *		  object target - target
 *		  string weapon - short desc of weapon used
 *		  int weapon_type - type of weapon (e.g. W_KNIFE)
 *		  int phurt	- how much percent of HP was reduced
 *		  string hitloc - what hitloc we hit
 *		  int phit	- how good was our hit in % from max
 *		  int dam	- damage caused in HP
 * Remark:	  This function should be masked as the default messages
 *		  are not very good
 */
void
dattack_message(object tp, object target,
		string weapon, int weapon_type,
		int phurt, string hitloc, int phit, int dam)
{
    if(phurt > 0)
    {
	tp->catch_tell("You hit "+target->query_the_name(tp)+"'s "+hitloc+" with your "+weapon+".\n");
	target->catch_tell(tp->query_The_name(target)+" hits your "+hitloc+" with "+HIS(tp)+" "+weapon+".\n");
	tp->tell_watcher(QCTNAME(tp)+" hits "+QTNAME(target)+"'s "+hitloc+" with "+HIS(tp)+" "+weapon+".\n");
    }
    else
    {
	tp->catch_tell("You miss "+target->query_the_name(tp)+".\n");
	target->catch_tell(tp->query_The_name(target)+" misses you.\n");
	tp->tell_watcher_miss(QCTNAME(tp)+" misses "+QTNAME(target)+".\n");
    }
}

/*
 * Function name: choose_dattack_weapon
 * Description:   Choose weapon to be used with special attack
 * Arguments:     object tp	- attacker that used special attack
 * Returns:       Object pointer to weapon or 0;
 */
object
choose_dattack_weapon(object tp)
{
    object *weapons = tp->query_weapon(-1);
    int dt = query_dattack_damage_type();

    if (!sizeof(weapons))
	return 0;

    if (!sizeof(weapons = filter(weapons, 
          &operator(&)(dt) @ &->query_dt())))
	return 0;

    return weapons[random(sizeof(weapons))];
}

/*******************************************************************/
/*******************************************************************/
/*******************************************************************/

private void
reset_dattack_special(object tp)
{
    if(!objectp(tp))
	return;
    tp->remove_prop(DATTACK_PROP);
    tp->catch_tell("You feel ready to go on the offensive again.\n");
    tp->special_command_enabled("dattack");
}

private void
do_dattack(object tp, object target, string attack)
{
    object combat_ob, weapon;
    int aid, hit, pen, dt, phurt, hitsuc, alarm;
    mixed why, dattack_resistance, *hit_result;

    if(!objectp(tp))
	return;

    alarm = set_alarm(query_dattack_relax_time(tp), 0.0,
			&reset_dattack_special(tp));
    tp->add_prop(DATTACK_PROP, alarm);

    if (!target)
	target = tp->query_attack();

    /* make sure the target is still in the same room as the attacker */
    if (!objectp(target) || (E(target) != E(tp)))
    {
	tp->catch_tell("The target for your "+attack+
	    " seems to have slipped away.\n");
	return;
    }

    if (!(weapon = choose_dattack_weapon(tp)))
    {
	tp->catch_tell("You can't "+attack+
	    "! You are not wielding an appropriate weapon.\n");
	return;
    }

    /* Has target become invalid somehow? */
    if (why = cannot_attack_target(tp, target, attack))
    {
	tp->catch_msg(why);
	return;
    }

    combat_ob = tp->query_combat_object();

    if (function_exists("try_hit", weapon) && !weapon->try_hit(target))
    {
	return;
    }

    aid = query_dattack_weapon_aid(tp, weapon);
    hit = query_dattack_weapon_hit(tp, weapon);

    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    if ((hitsuc = combat_ob->cb_tohit(aid, hit, target)) > 0)
    {
	pen = query_dattack_weapon_pen(tp, weapon);
	pen = F_PENMOD(pen, query_dattack_skill(tp));
	if (intp(dattack_resistance = target->query_prop("_live_m_no_"+attack)))
	{
	    pen = pen * (100 - dattack_resistance) / 100;
	}

	dt = query_dattack_damage_type();
	hit_result = target->hit_me(pen, dt, tp, aid);
	DBGMSG("*** Dattack pen: "+pen+", result: "+hit_result[0]+","+
	    hit_result[1]+","+hit_result[2]+","+hit_result[3]+" ***\n");
    }
    else
    {
	hit_result = target->hit_me(hitsuc, 0, tp, aid);
	DBGMSG("*** Dattack miss, result: "+hit_result[0]+","+
	    hit_result[1]+","+hit_result[2]+","+hit_result[3]+" ***\n");
    }

    if (hit_result[1])
    {
/*
	weapon->did_hit(aid, hit_result[1], hit_result[0], target, dt,
				hitsuc, hit_result[3]);
*/
	weapon->set_weapon_hits(weapon->query_weapon_hits() + 1);
    }

    applyv(&dattack_message(tp, target, weapon->short(),
			weapon->query_wt()), hit_result);

    if (tp->query_fatigue() < 5)
    {
	tp->heal_hp(-(5 - tp->query_fatigue()));
	tp->set_fatigue(0);
	tp->catch_tell("The strain of the attack drains you.\n");
    }
    else
    {
	tp->add_fatigue(-5);
    }

    phurt = hit_result[0]; 
    if (phurt >= 0)
    {
	tp->add_panic(-3 - phurt / 5);

	if (target->query_hp() <= 0)
	{
	    dattack_do_die(tp, target);
	}
    }
    else
    {
	tp->add_panic(1);
    }
}

int
dattack(string str)
{
    object ob, tp = TP;
    int alarm;
    mixed *call;
    string verb = query_verb();
    string tmp;

    if(!verb)
	verb = "attack";

    /* Is the attacker already busy? */
    alarm = tp->query_prop(DATTACK_PROP);
    if(alarm)
    {
	call = get_alarm(alarm);
	if (call)
	{
	    switch(call[1])
	    {
	    case "do_dattack":
		NF("You are already preparing "+verb+".\n");
		break;
	    default:
		NF("You are not yet ready to "+verb+". Patience!\n");
	    }
	    return 0;
	}
	else
	{
	    DBGMSG("*** WARNING!!!  DATTACK_PROP set and alarm not found! ***\n");
	    /* should not happen but we check it for safety */
	    tp->remove_prop(DATTACK_PROP);
	}
    }

    if (!(ob = get_one_target_from_string(str, verb)))
	return 0;

    if (!choose_dattack_weapon(tp))
    {
	NF("You are not wielding an appropriate weapon.\n");
	return 0;
    }

    write("Your muscles tense as you prepare to "+verb+".\n");
/*
    tp->tell_watcher(QCTNAME(tp) + "'s muscles tense as "+HE(tp)+
		" readies for battle.\n");
*/

    tp->reveal_me();

    if (ob != tp->query_attack())
    {
	tp->attack_object(ob);
	tp->catch_tell("You attack " + ob->query_the_name(tp) + ".\n");
	tp->tell_watcher(QCTNAME(tp) + " attacks " + QTNAME(ob) + ".\n", ob);
	ob->catch_tell(tp->query_The_name(ob) + " attacks you!\n");
    }
    else
    {
	ob = 0;
    }

    alarm = set_alarm(query_dattack_prepare_time(tp), 0.0,
			&do_dattack(tp, ob, verb));
    tp->add_prop(DATTACK_PROP, alarm);

    return 1;
}

mixed
cannot_attack_target(object tp, object ob, string attack)
{
    mixed tmp;
    string qtname = ob->query_the_name(tp);

    if (!tp->can_see_in_room() && !tp->query_attack())
       return "You can't see your target.\n";

    if (!ob->check_seen(tp) && ob != tp->query_attack())
    {
	return "The target of your "+attack+" has escaped!\n";
    }

    /* check if stunned */
    if (tp->query_prop(LIVE_I_STUNNED) ||
        (tp->query_prop(LIVE_I_ATTACK_DELAY)))
    {
        return "You are too stunned to "+attack+"!\n";
    }

    /* check NO_ATTACK properties */
    if (stringp(tmp = ob->query_prop("_live_m_no_"+attack)) ||
	(tmp = environment(ob)->query_prop(ROOM_M_NO_ATTACK)) ||
	(tmp = ob->query_prop(OBJ_M_NO_ATTACK)))
    {
	if (stringp(tmp))
	{
	    return tmp;
	}
	else
	{
	    return "You feel a divine force protecting "+qtname+".\n";
	}
    }
    /* Someone might try defining this to block all special attacks */
    if (ob->query_not_attack_me(tp, -1))
    {
	/* A message should be given by query_not_attack_me() */
	return "";
    }
    /* next two checks only if not already fighting ob */
    if(member_array(ob, tp->query_enemy(-1)) == -1)
    {
	/*** check DIS ***/
	if (!F_DARE_ATTACK(tp, ob))
	{
	    return "You don't dare to "+attack+" "+qtname+".\n";
	}
	/*** confirm attack on introduced person ***/
	if ((!tp->query_npc()) &&
	    (tp->query_met(ob)) &&
	    (tp->query_prop(LIVE_O_LAST_KILL) != ob))
	{
	    tp->add_prop(LIVE_O_LAST_KILL, ob);
	    return C(attack)+" "+qtname+"?!? Please confirm by trying again.\n";
	}
    }
    return 0;
}

int
kill_access(object ob)
{
    return !((!living(ob)) ||
             (ob->query_ghost()) ||
             (ob == TP) ||
	     (!ob->check_seen(TP)));
}

varargs object
get_one_target_from_string(string str, string verb = "attack", int friendly = 0)
{
    object *obj, ob;
    mixed tmp;

    /* check if stunned */
    if (TP->query_prop(LIVE_I_STUNNED) ||
        TP->query_prop(LIVE_I_ATTACK_DELAY))
    {
        NF("You are too stunned to be able to "+verb+"!\n");
        return 0;
    }

    if (!strlen(str))
    {
	if (friendly)
	{
	    NF("Who do you want to "+verb+"?\n");
	    return 0;
	}
        if (!(ob = TP->query_attack()))
        {
            NF("But you are not fighting anyone.\n");
            return 0;
        }
    }
    else
    {
        if (!sizeof(obj = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access")))
        {
            NF("You find no such living creature.\n");
            return 0;
        }
        if (sizeof(obj) > 1)
        {
            NF("Be specific, you can't "+verb+" "+
               COMPOSITE_ALL_LIVE(obj) + " at the same time.\n");
            return 0;
        }
        ob = obj[0];
    }
    if (friendly)
    {
	if (member_array(ob, TP->query_enemy(-1)) != -1)
	{
	    NF("But you are in fight with "+QTNAME(ob)+"!\n");
	    return 0;
	}
    }
    else 
    {
	if (tmp = cannot_attack_target(TP, ob, verb))
	{
	    NF(tmp);
	    return 0;
	}
    }
    return ob;
}
