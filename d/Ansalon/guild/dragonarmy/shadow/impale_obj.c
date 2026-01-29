/*
 * This objects does all that is necessary to do impaling defensive
 * special.
 *
 * All you have to do is call function
 * do_impale(object who, object ob, int was_fighting)
 * Arguments: who - object that is doing this special
 *	      ob  - object that attacked who
 *	      was_fighting - 0 who was not fighting before
 *			     1 who was already fighting
 *
 * Created by Milan for Red Dragonarmy
 * Messages altered by Arman 22/8/98
 *
 * Navarre June 15th 2007: Changed recovery from
 *                         autoimpale message to tell_room
 *                         instead of tell_watcher.
 *
 * Navarre April 26th 2008: Removed a forced flee when autoimpale is run.
 *                          We have a global attack check that makes people flee
 *                          if the guy attacking them is too big. Lets just
 *                          use that check.
 *                          It prevented bigger DAs bringing smaller DAs into combat
 *                          and we do want people to team.
 */
#pragma strict_types
#pragma save_binary
#pragma no_clone
#pragma no_inherit

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../guild.h"

/* Prototype */
void make_stun(object ob, int time);

private void
impale_message(object who, object ob, string weapon, int phurt, string hitloc, int phit, int dam)
{
    string msg0, msg1, msg2;
    string name = ob->query_the_name(who);
    string Name = ob->query_The_name(who);
    string myname = who->query_the_name(ob);

    if (phurt >= 0)
    {
	switch (dam)
	{
	case 0:
	    msg0 = "At the last second, " +name+ " manages to knock aside "+
	    "your " +weapon+ ", avoiding a painful injury.\n";
	    msg1 = "At the last second, you manage to knock aside "+
	    myname+ "'s " +weapon+ ", narrowly avoiding " +
	    "impaling yourself on it.\n";
	    msg2 = "At the last second, " +QTNAME(ob)+ " manages to knock "+
	    "aside " +QTNAME(who)+ "'s " +weapon+ ", narrowly " +
	    "avoiding impaling " +HIM(ob)+ "self on it.\n";
	    break;
	case 1..10:
	    msg0 = "As " +name+ " charges into battle, you calmly thrust forward, " +
	    "impaling " + HIS(ob)+ " " +hitloc+ " with your " +
	    weapon + ".\n";
	    msg1 = "As you charge into battle, " +myname+
	    " calmly thrusts forward with " +HIS(who)+ " " +weapon+
	    ", impaling your " +hitloc+ "!\n";
	    msg2 = "As " +QTNAME(ob)+ " charges into battle, " +QTNAME(who)+
	    " calmly thrusts forward with " +HIS(who)+ " " +weapon+
	    ", impaling " +QTNAME(ob)+ "'s " +hitloc+ ". The blow " +
	    "seems to have shocked " +QTNAME(ob)+ " into inaction.\n";
	    break;
	case 11..25:
	    msg0 = "You inwardly chuckle with dark amusement as " +name+
	    " throws " +HIM(ob)+ "self forward into battle, conveniently onto the " +
	    "end of your " +weapon+ ". "+Name+ "'s eyes widen " +
	    "most satisfactorily in pain and shock.\n";
	    msg1 = "The dark amusement on " +myname+ "'s face warns you " +
	    "too late of the foolishness of your charge, your " +
	    hitloc+ " being impaled deeply on " +HIS(who)+ " "+ weapon+
	    "!\n";
	    msg2 = QCTNAME(ob)+ "'s eyes widen in pain and shock, " +HIS(ob)+ " "+
	    hitloc+ " impaled deeply on " +QTNAME(who)+ "'s " +weapon+
	    ".\n";
	    break;
	default:
	    msg0 = "In a blind charge, " +name+ " throws " +HIM(ob)+ "self onto " +
	    "the end of your " +weapon+ ", impaling " +HIM(ob)+"self " +
	    "badly and effectively incapacitating " +HIM(ob)+ "self.\n";
	    msg1 = "In a blind charge, you throw yourself upon " +myname+
	    ". Unfortunately for you, the attack was anticipated, and " +
	    "you find yourself badly impaled on the end of " +HIS(who)+
	    " " +weapon+ ".\n";
	    msg2 = "In a blind charge, " +QTNAME(ob)+ " throws " +HIM(ob)+ "self " +
	    "onto the end of " +QTNAME(who)+ "'s " +weapon+ ", impaling " +
	    HIM(ob)+ "self badly, and effectively incapacitating " +
	    HIM(ob)+ "self.\n";
	}
    }
    else
    {
	msg0 = Name+ " avoids your attempts to impale " +HIM(ob)+
	", entering into close combat with you!\n";
	msg1 = "You avoid " +myname+ "'s attempts to impale you, " +
	"and enter into close combat with " +HIM(who)+ "!\n";
	msg2 = QCTNAME(ob)+ " avoids " +QTNAME(who)+ "'s attempts " +
	"to impale " +HIM(ob)+ ", and the two enter into close " +
	"combat with each other!\n";
    }
    who->catch_tell(msg0);
    ob->catch_tell(msg1);
    who->tell_watcher(msg2, ob);
}

/* This routine can be made smarter.  For now, just choose a
 * random impaling polearm
 */
private object
choose_weapon(object who)
{
    object *weapons;

    if (!sizeof(weapons = who->query_weapon(-1)))
	return 0;

    if (!sizeof(weapons = filter(weapons,
	  &operator(==)(W_POLEARM) @ &->query_wt())))
	return 0;

    if (!sizeof(weapons = filter(weapons,
	  &operator(&)(W_IMPALE) @ &->query_dt())))
	return 0;

    return weapons[random(sizeof(weapons))];
}

void
do_impale(object who, object ob, int was_fighting)
{
    object weapon, combat_ob;
    int aid, hitsuc, phurt, attdex, stun_time, pen;
    mixed *hit_result;

    /* do we see attacking enemy? */
    if (!ob->check_seen(who))
    {
	DBGMSG("*** enemy not seen ***\n");
	return;
    }

    /* aren't we stunned? */
    if (who->query_prop(LIVE_I_ATTACK_DELAY) || who->query_prop(LIVE_I_STUNNED))
    {
	DBGMSG("*** we are stunned ***\n");
	return;
    }

    /* do we have proper weapon? */
    if (!(weapon = choose_weapon(who)))
    {
	DBGMSG("*** missing impaling polearm ***\n");
	return;
    }

    attdex = random(ob->query_stat(SS_DEX));
    /* Are we quick enough? */
    if (random(who->query_stat(SS_DEX) + who->query_skill(SS_AWARENESS) +
	(3*who->query_skill(SS_APPR_MON)))    <   attdex)
    {
	who->catch_tell("The attack was too quick to counter it with your "+
	  weapon->short()+".\n");
	return;
    }

    /* Are we skilled enough to do it even while fighting? */
    if (was_fighting &&
      random(who->query_skill(SS_DEFENCE) + who->query_skill(SS_DRAGONARMY_ATTACK)) < attdex)
    {
	who->catch_tell("Being already in battle, you find yourself " +
	  "unable to counter this new opponent with your " +
	  weapon->short()+".\n");
	return;
    }

    who->catch_tell("You quickly turn the point of your " +weapon->short()+ " towards "+
      ob->query_the_name(who)+".\n");
    ob->catch_tell(who->query_The_name(ob)+ " quickly turns the point of " +
      HIS(who)+ " " +weapon->short()+
      " towards you.\n");
    who->tell_watcher(QCTNAME(who)+" quickly turns the point of " +
      HIS(who)+ " " +weapon->short()+
      " towards "+QTNAME(ob)+".\n", ob);

    aid = weapon->query_hands();

    /* Someone might try defining this to block attack */
    if (ob->query_not_attack_me(who, aid))
    {
	DBGMSG("*** blocked by query_not_attack_me() ***\n");
	return;
    }

    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    combat_ob = who->query_combat_object();
    if ((hitsuc = combat_ob->cb_tohit(aid, 2*weapon->query_hit(), ob)) > 0)
    {
	pen = 2*weapon->query_pen();
	pen = F_PENMOD(pen, who->query_skill(SS_DRAGONARMY_ATTACK));
	hit_result = ob->hit_me(pen, W_IMPALE, who, aid);
	DBGMSG("*** hit, hit_result: "+hit_result[0]+","+hit_result[1]+","+hit_result[2]+","+hit_result[3]+" ***\n");
    }
    else
    {
	hit_result = ob->hit_me(hitsuc, 0, who, aid);
	DBGMSG("*** miss, hit_result: "+hit_result[0]+","+hit_result[1]+","+hit_result[2]+","+hit_result[3]+" ***\n");
    }

    applyv(&impale_message(who, ob, weapon->short()), hit_result);

    if (hit_result[1])
    {
/*
	weapon->did_hit(aid, hit_result[1], hit_result[0], ob, W_IMPALE,
	  hitsuc, hit_result[3]);
*/
	weapon->set_weapon_hits(weapon->query_weapon_hits() + 1);
    }

    phurt = hit_result[0]; 

    if (phurt >= 0)
    {
	who->add_panic(-3 - phurt / 5);
	if (ob->query_hp() <= 0)
	{
	    ob->do_die(who);
	}
	else
	{
	    stun_time = MIN(20, hit_result[3] / 10);
	    switch (hit_result[1])
	    {
	    case "head":
		stun_time += 10;
		break;
	    case "body":
		stun_time += 5;
	    }
	    if (stun_time > 0 && hit_result[3] > 0)
	    {
		DBGMSG("*** stun time: "+stun_time+" sec ***\n");
		make_stun(ob, stun_time);
	    }
	}
    }
    else
    {
	who->add_panic(1);
    }
}

private void end_stun(object ob)
{
    if (!objectp(ob))
	return;

    ob->remove_stun();
    if (ob->query_prop(LIVE_I_STUNNED) > 0)
    {
	ob->catch_tell("You recover somewhat from the shock of your " +
	  "wound.\n");
    }
    else
    {
	ob->catch_tell("You feel completely recovered from the " +
	  "shock of the wound.\n");
	tell_room(environment(ob), QCTNAME(ob) + " seems to have recovered " +
		  "from the shock of being impaled.\n", ob);
    }
}

private void make_stun(object ob, int time)
{
    ob->add_stun();
    if (ob->query_prop(LIVE_I_STUNNED) > 1)
    {
	ob->catch_tell("The wound incapacitates you further!\n");
    }
    else
    {
	ob->catch_tell("The pain and shock of the wound incapacitates you!\n");
    }
    set_alarm(itof(time), 0.0, &end_stun(ob));
}
