/*
 /std/combat/cbase.c

 This is the externalized combat routines. 

 This object is cloned and linked to a specific individual when
 engaged in combat. The actual object resides in 'limbo'.

 Ver 2.0 JnA: 911220

   This version uses an attack and defence table. Combat no longer have
   a concept of weapons and armours. Only attacks and hitlocations.

   This file is meant to be inherited by more advanced combat systems.

 Note that this is the implementation of the combat system in general. If
 you want to make an entirely different combat system, you are recommended
 to change the 'COMBAT_FILE' define in config.h

*/
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <math.h>
#include <comb_mag.h>
#include "combat.h"
#include "/lib/profile.c"

/*
 * Prototypes
 */
public nomask int cb_query_panic();
public nomask void cb_attack(object ob);
static nomask int fixnorm(int offence, int defence);

/*
 * This object is not movable
 */
nomask int move(mixed dest, mixed nocheck) 
{ 
    return 1; 
}

/*
    Format of each element in the attacks array:

         ({ wchit, wcpen, dt, %use, skill })
              wchit: Weapon class to hit
              wcpen: Weapon class penetration
	      dt:    Damage type
              %use:  Chance of use each turn
   	      skill: The skill of this attack (defaults to wcpen)
	      m_pen: The modified pen used in combat

	 att_id:    Specific id, for humanoids W_NONE, W_RIGHT etc

    Format of each element in the hitloc_ac array:

         ({ *ac, %hit, desc })
	      ac:    The ac's for each damagetype for a given hitlocation
	      %hit:  The chance that a hit will hit this location
	      desc:  String describing this hitlocation, ie "head", "tail"
	      m_ac:  Modified ac to use in combat
                       .......
	 Note that the sum of all %hit must be 100.

         hit_id:    Specific id, for humanoids, A_TORSO, A_HEAD etc
*/

static int      *att_id,        /* Id's for attacks */
                *hit_id,        /* Id's for hitlocations */
                panic,          /* Dont panic... */
                panic_time,     /* Time panic last checked. */
		tohit_val,	/* A precalculated tohit value for someone */
		hit_heart,	/* Controls the quickness when fighting. */
		i_see_combat,	/* True if the living shall get cb-messages. */
                alarm_id;       /* The id of the heart_beat alarm */

static float    speed,          /* How often I hit */
                delay;

static mixed    *attacks,       /* Array of each attack */
                *hitloc_ac;	/* The armour classes for each hitloc */

static object   me,             /* The living object concerned */
                *enemies,	/* Array holding all living I hunt */
		tohit_ob,	/* Last object we calculated tohit values */
                attack_ob;	/* Object to attack == Current enemy. */

/*
 * Description: Give status information about the combat values
 *
 */
public string
cb_status()
{
    string str;
    int il, tmp, size;
    mixed ac;
    object *valid_enemies;

    enemies = enemies - ({ 0 }); /* Maybe some old enemy is dead?? */

    str = "Living object: " + file_name(me) + 
	" (Uid: " + getuid(me) + ", Euid: " + geteuid(me) + ")\n";

    str += "Combat object: " + file_name(this_object()) + 
	" (Uid: " + getuid(this_object()) + 
	    ", Euid: " + geteuid(this_object()) + ")\n";

    if (attack_ob)
	str += "Fighting: " + attack_ob->query_name() +
	    " (" + file_name(attack_ob) +")\n";

    /* if the enemies have been destroyed then it can cause problems
     * so remove the non live ones.  Left
     */
    valid_enemies = FILTER_LIVE(enemies);

    if (sizeof(valid_enemies))
       str += "Enemies:\n" + break_string(COMPOSITE_LIVE(valid_enemies), 76, 3);
    else
	str += "No enemies pending";

    str += sprintf("\nPanic: %3d, Attacks: %3d, Hitlocations: %3d\n",
		   cb_query_panic(), sizeof(att_id), sizeof(hit_id));

    il = -1;
    size = sizeof(att_id);
    while(++il < size)
    {
	if (!il)
	    str += sprintf("\n%-20s %@|9s\n","  Attack",
			   ({"wchit",
			     "impale/slash/bludg ", "wcskill",
			     "   %use" }));
	ac = attacks[il][ATT_DAMT];
	ac = ({ (ac & W_IMPALE ? attacks[il][ATT_WCPEN][0] + " " : "no "),
		(ac & W_SLASH ? attacks[il][ATT_WCPEN][1] + " " : "no "), 
		(ac & W_BLUDGEON ? attacks[il][ATT_WCPEN][2] + " " : "no ") });
	ac = implode(ac,"   ");

	str += sprintf("%-20s %|9d %-17s %|9d %|9d\n", 
		       this_player()->check_call(
			    this_object()->cb_attack_desc(att_id[il])) + ":",
		       attacks[il][ATT_WCHIT],
		       ac,
		       attacks[il][ATT_SKILL],
		       attacks[il][ATT_PROCU]);
    }

    il = -1;
    size = sizeof(hit_id);
    while(++il < size)
    {
	if (!il)
	    str += sprintf("\n%-15s %@|9s\n","  Hit location",
			   ({"impale", "slash", "bludgeon", " %hit" }));
	str += sprintf("%-15s", hitloc_ac[il][HIT_DESC] + ":") + " ";
	ac = hitloc_ac[il][HIT_AC];
	if (!pointerp(ac))
	    ac = ({ ac, ac, ac });
	else 
	    ac = ac[0..2];
	str += sprintf("%@|9d %|9d\n", ac, hitloc_ac[il][HIT_PHIT]);
    }

    str += "\nParry: " + me->query_skill(SS_PARRY) + "  Defense: " + 
	me->query_skill(SS_DEFENSE) + "  Stat av: " +
	(tmp = me->query_average_stat()) + "  Dex: " + me->query_stat(SS_DEX) +
	"  Enc: " + (me->query_encumberance_weight() +
		me->query_encumberance_volume() / 2) + "\nVol: " +
	me->query_prop(CONT_I_VOLUME) + "  Speed: " +
	me->query_prop(LIVE_I_QUICKNESS) + "  Exp at kill: " +
	(F_KILL_GIVE_EXP(tmp) *
		(me->query_npc() ? me->query_exp_factor() / 100 : 1)) + "\n";

    return str;
}

/*
 * Function name: cb_data
 * Description:   More data about combat stats.
 * Returns:	  A string to write
 */
string
cb_data()
{
    string str;
    int i, val, tmp, t2, ac, size;
    object *arr;

    str = "Living object: " + file_name(me) +
        " (Uid: " + getuid(me) + ", Euid: " + geteuid(me) + ")\n";

    str += "Combat object: " + file_name(this_object()) +
        " (Uid: " + getuid(this_object()) +
            ", Euid: " + geteuid(this_object()) + ")\n";

    val = 2 * fixnorm(me->query_stat(SS_DEX), 50) -
	fixnorm(me->query_prop(CONT_I_VOLUME), 60000) -
	fixnorm(me->query_encumberance_weight() +
		me->query_encumberance_volume(), 60);

    tmp = 0;
    i = -1;
    size = sizeof(att_id);
    while(++i < size)
    {
        tmp += attacks[i][ATT_WCHIT] * attacks[i][ATT_PROCU];
    }
    tmp /= 100;

    val += 4 * fixnorm(2 * tmp, 50);

    str += sprintf("\n%-20s %5d\n", "Offensive tohit:", val);

    i = -1;
    size = sizeof(att_id);
    while(++i < size)
    {
	ac = attacks[i][ATT_DAMT];
	if (ac & W_IMPALE)
	    tmp = attacks[i][ATT_M_PEN][0];
        else if (ac & W_SLASH)
	    tmp = attacks[i][ATT_M_PEN][1];
	else if (ac & W_BLUDGEON)
            tmp = attacks[i][ATT_M_PEN][2];
	val += tmp * attacks[i][ATT_PROCU];
    }
    val /= 100;

    str += sprintf("%-20s %5d\n", "Offensive pen:", val);

    val = 2 * fixnorm(50, me->query_stat(SS_DEX)) -
        fixnorm(60000, me->query_prop(CONT_I_VOLUME)) -
        fixnorm(60, me->query_encumberance_weight() +
                me->query_encumberance_volume());

    if (sizeof((object *)me->query_weapon(-1) - ({ 0 })))
	tmp = me->query_skill(SS_PARRY);
    else
	tmp = me->query_skill(SS_UNARM_COMBAT) / 2;

    tmp += me->query_skill(SS_DEFENSE);

    val += 4 * fixnorm(70, tmp);

    str += sprintf("%-20s %5d\n", "Defensive tohit:", val);

    val = 0;
    i = -1;
    size = sizeof(hit_id);
    while(++i < size)
    {
        val += hitloc_ac[i][HIT_M_AC][0] * hitloc_ac[i][HIT_PHIT];
    }
    val /= 100;

    str += sprintf("%-20s %5d\n", "Defensive ac:", val);

    str += "\nExp at kill: " + (F_KILL_GIVE_EXP(me->query_average_stat()) *
         (me->query_npc() ? me->query_exp_factor() : 100) / 100) +
	 "  Speed: " + me->query_prop(LIVE_I_QUICKNESS);

    arr = all_inventory(me);
    i = -1;
    size = sizeof(arr);
    while(++i < size)
    {
	tmp += arr[i]->query_prop(OBJ_I_VALUE);
    }
    str += "  Carried value: " + tmp + " (" + sizeof(arr) + ") objects.\n";

    return str;
}

/*
 * Function name: create_object
 * Description:   Reset the combat functions
 */
public nomask void
create_object()
{
    start_profiling();
    panic_time = time();
    if (me)
	return;
    att_id = ({}); 
    hit_id = ({});
    hitloc_ac = ({}); 
    attacks = ({});
    enemies = ({});
    delay = 0.0;
    this_object()->create_cbase();
}

/*
 * Function name: clean_up
 * Description:   This function is called when someone wants to get rid of
 *		  this object, but is not sure if it is needed. Usually
 *		  called from the GD, or via call_out() from remove_object()
 */
public void
clean_up()
{
    if (!objectp(me))
	destruct();
}

/*
 * Function name: remove_object
 * Description:   See if we can safely remove this object. If me exists
 *		  then this object will not be removed. Use the -D flag
 *		  if you really want to get rid of this object.
 */
public void
remove_object()
{
    set_alarm(1.0, 0.0, "clean_up");
}

/*
 * Function name: combat_link
 * Description:   Called by the internal combat routines on startup
 */
public void 
cb_link()
{
    if (objectp(me))
	return;

    me = previous_object();
    i_see_combat = me->query_see_special_msg();
}

/*
 * Description: Return the connected living
 */
public object qme() 
{ 
    return me; 
}

/*
 * Function name: cb_configure
 * Description:   Configure attacks and hitlocations.
 */
public void
cb_configure()
{
    att_id = ({}); 
    hit_id = ({});
    hitloc_ac = ({}); 
    attacks = ({});
}

/*
 * Function name: cb_add_panic
 * Description:   Adjust the panic level.
 * Arguments:     dpan:  The panic increase/decrease
 */
public void
cb_add_panic(int dpan)
{
    int oldpan;

    oldpan = cb_query_panic();

    panic += dpan; 
    if (panic < 0) 
	panic = 0; 

    if (!panic && oldpan)
	tell_object(me, "You feel calm again.\n");
}

/*
 * Function name: cb_query_panic
 * Description:   Give the panic level.
 */
public int
cb_query_panic() 
{ 
    int n, chk;

    if (objectp(attack_ob))
        panic_time = time(); /* So we don't heal panic while fighting */
    else 
    {
        n = (time() - panic_time) / F_INTERVAL_BETWEEN_PANIC_HEALING;
        if (n > 0 && (chk = (1 << n)) > 0)
        {
            if (panic > 0)
                panic = panic / chk;
            panic_time += n * F_INTERVAL_BETWEEN_PANIC_HEALING;
        }
    }

    return panic; 
}

/*
 * Function name: cb_may_panic
 * Description:   Check on our panic level, act accordingly.
 */
public void
cb_may_panic()
{
    int il, size;
    object *tm;

    if (random(cb_query_panic()) > (10 + (int)me->query_stat(SS_DIS) * 3))
    {
	tell_object(me,"You panic!\n");
	tell_room(environment(me), QCTNAME(me) + " panics!\n");
	tm = (object*)me->query_team_others();
	size = sizeof(tm);
	il = -1;
	while(++il < size)
	{
	    if (environment(me) == environment(tm[il]))
		tm[il]->add_panic(25);
	}
	me->run_away();
    }
}

/*
 * Function name: cb_adjust_combat_on_intox
 * Description:   Called to let intoxication affect combat. This
 *                is used to do nasty drunk type things *laugh*
 * Arguments:     pintox: %intoxicated      
 */
public void
cb_adjust_combat_on_intox(int pintox)
{
    object *p;

    if (pintox < 90)
	return;

    p = all_inventory(environment(me));

    if (!sizeof(p))
    {
	/* Here we check for neat things to do */
    }
}

/*
 * Normalize offensive / defensive values
 *
 */
static nomask int
fixnorm(int offence, int defence)
{
   if (offence + defence == 0)
       return 0;

   return ((100 * offence) / (offence + defence)) - 50;
}

/*
 * Function name: cb_update_tohit_val
 * Description:   Update the tohit value for some object. Changing ones
 *		  encumberance while fighting will not have any effect
 *		  unless this function is called, but I think it's worth
 *		  it since we save cpu.
 * Arguments:	  ob - The object we shall try to hit
 *		  weight - If the formula should be weighted any way.
 */
varargs void
cb_update_tohit_val(object ob, int weight)
{
    tohit_ob = ob;
    tohit_val = 2 * fixnorm(me->query_stat(SS_DEX), ob->query_stat(SS_DEX)) -
	fixnorm(me->query_prop(CONT_I_VOLUME), ob->query_prop(CONT_I_VOLUME)) -
	fixnorm(me->query_encumberance_weight() + me->query_encumberance_volume(),
	    ob->query_encumberance_weight() + ob->query_encumberance_volume());
    tohit_val += weight;
}

/*
 * Function name: cb_tohit
 * Description:   Decide if we hit our victim or not. This should depend
 *		  on wchit and skill/stat differences me/victim
 * Arguments:     aid:   The attack id
 *                wchit: Weapon class 'to hit'
 *                vic:   The intended victim
 * Returns:       True if hit, otherwise a negative value indicating how much
 *		  we failed.
 */
public int
cb_tohit(int aid, int wchit, object vic)
{
    int tmp, whit, bskill, bskill_tmp;

    /*
     * Four factors are normalized (-50, 50) in the 'to-hit'.
     * 1 - Weapon class 'to hit' <-> Defensive skill
     * 2 - Weight
     * 3 - Volume
     * 4 - Dexterity
     * These are weighted with the factors (4, 1, 1, 2)
     */

    if (sizeof((object *)vic->query_weapon(-1) - ({ 0 })))  /* Any weapons ? */
	tmp = (int) vic->query_skill(SS_PARRY);
    else
	tmp = (int) vic->query_skill(SS_UNARM_COMBAT) / 2;

    tmp += vic->query_skill(SS_DEFENSE);

    /*
     * Is it dark or opponent invis? Then how well do we fight?
     */

    if (!CAN_SEE_IN_ROOM(me) ||
	(vic->query_prop(OBJ_I_INVIS) > me->query_prop(LIVE_I_SEE_INVIS)))
    {
	/* A npc shouldn't loose all fightingskill if it is dark and no
	 * blind fight skill is set. */
	bskill = me->query_skill(SS_BLIND_COMBAT);
	bskill = ((bskill == 0) && me->query_npc()) ? 40 : bskill;
	wchit = bskill * wchit / 100;
    }
    if (!CAN_SEE_IN_ROOM(vic) ||
	(me->query_prop(OBJ_I_INVIS) > vic->query_prop(LIVE_I_SEE_INVIS)))
    {
	bskill_tmp = vic->query_skill(SS_BLIND_COMBAT);
        bskill_tmp = ((bskill_tmp == 0) && vic->query_npc()) ? 40 : bskill_tmp;
	tmp = bskill_tmp * tmp / 100;
    }

    whit = 4 * fixnorm(random(wchit) + random(wchit) + 
		       random(wchit) + random(wchit), random(tmp));

    if (vic != tohit_ob)
	cb_update_tohit_val(vic);

    whit += tohit_val;

    if (whit > 0)
	return 1;
    else
	return whit - 1;
}

/*
 * Function name: cb_try_hit
 * Description:   Decide if we a certain attack fails because of something
 *                related to the attack itself, ie specific weapon that only
 *		  works some of the time. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from heart_beat)
 * Arguments:     aid:   The attack id
 * Returns:       True if hit, otherwise 0.
 */
public int
cb_try_hit(int aid) 
{ 
    return 1; 
}

/*
 * Function name: cb_got_hit
 * Description:   Tells us that we got hit. It can be used to reduce the ac
 *                for a given hitlocation for each hit. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from cb_hit_me)
 * Arguments:     hid:   The hitloc id
 *                ph:    The %hurt
 *                att:   Attacker
 *		  aid:   The attack id of the attacker
 *                dt:    The damagetype
 *		  dam:	 The number of hitpoints taken
 */
public varargs void
cb_got_hit(int hid, int ph, object att, int aid, int dt, int dam) 
{
}

/*
 * Function name: cb_attack_desc
 * Description:   Gives the description of a certain attack slot. This is
 *		  supposed to be replaced by more intelligent routines in
 *                humanoid and creature combat
 * Arguments:     aid:   The attack id
 * Returns:       string holding description
 */
public string
cb_attack_desc(int aid)
{
    return "body";
}

/* 
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:	  str   - The string to send
 *		  enemy - Who the enemy was
 *		  arr   - Array of objects never to send message
 */
varargs void
tell_watcher(string str, object enemy, mixed arr)
{
    object *ob;
    int i, size;

    ob = all_inventory(environment(me)) - ({ me, enemy });

    if (arr)
    {
	if (pointerp(arr))
	    ob -= arr;
	else
	    ob -= ({ arr });
    }

    i = -1;
    size = sizeof(ob);
    while(++i < size)
    {
	if (ob[i]->query_see_blood() && CAN_SEE_IN_ROOM(ob[i]))
	{
	    if (CAN_SEE(ob[i], me))
	    	ob[i]->catch_msg(str);
	    else
		tell_object(ob[i], enemy->query_The_name(ob[i]) +
		    " is hit by someone.\n");
	}
    }
}

/*
 * Function name: cb_did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. This is supposed to be
 *                replaced by a more intelligent routine in creature and
 *                humanoid combat. (called from heart_beat)
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *		  dt:	 The current damagetype
 *		  phit:  The %success that we made with our weapon
 *			 If this is negative, it indicates fail
 *		  dam:   Damage we did in hit points
 */
public varargs void
cb_did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
	   int phit, int dam)
{
    string how;
    string what;
    string owhat;
    string with;
    string where;

    if ((!objectp(enemy)) || (!objectp(me)))
    {
	return;
    }

    with = cb_attack_desc(aid);

    if (phurt == -1 || phurt == -2)
    {
	cb_add_panic(1);

	if (i_see_combat)
	{
	    me->catch_msg("You aim for the " + hdesc + " of " +
		enemy->query_the_name(me) + " with your " + with +
		" but miss.\n");
	}
	if (enemy->query_see_special_msg())
	{
	    enemy->catch_msg(me->query_The_name(enemy) + " aims for your " +
		hdesc + " with " + me->query_possessive() + " " + with +
		", but misses.\n");
	}
	tell_watcher(QCTNAME(me) + " aims for the " + hdesc + " of " +
	    QTNAME(enemy) + " with " + me->query_possessive() + " " +
	    with + ", but misses.\n", enemy);
	return;
    }

    cb_add_panic(-3 - (phurt / 5));
    where = " the " + hdesc + " of ";

    switch (phurt)
    {
    case 0..4:
	how = ".\n";
	what = "tickle";
	owhat = "tickles";
	break;
    case 5..9:
	how = ".\n";
	what = "graze";
	owhat = "grazes";
	break;
    case 10..19:
	how = ".\n";
	what = "hurt";
	owhat = "hurts";
	break;
    case 20..29:
	how = ", rather bad.\n";
	what = "hurt";
 	owhat = "hurts";
	break;
    case 30..49:
	how = ", very bad.\n";
	what = "hurt";
	owhat = "hurts";
	break;
    case 50..69:
	how = ", very hard.\n";
	what = "smash";
	owhat = "smashes";
	break;
    case 70..89:
	how = ", with a bone crushing sound.\n";
	what = "smash";
	owhat = "smashes";
	where = " ";
	break;
    default:
	how = ".\n";
	what = "massacre";
	owhat = "massacres";
	where = " ";
    }

    if (i_see_combat)
    {
	me->catch_msg("You " + what + where + enemy->query_the_name(me) +
	    " with your " + with + how);
    }
    if (enemy->query_see_special_msg())
    {
	enemy->catch_msg(QCTNAME(me) + " " + owhat + " your " + hdesc +
	    " with " + me->query_possessive() + " " + with + how);
    }
    tell_watcher(QCTNAME(me) + " " + owhat + where + QTNAME(enemy) +
	" with " + me->query_possessive() + " " + with + how, enemy);
}

/*
 * Function name: cb_reward
 * Description:   Reward the attacker of 'me'. Can be replaced.
 * Arguments:	  attacker:   Enemy that attacks 'me'
 *                dam:        The amount of damage in hitpoints made
 *                kill:       True if the attack killed me
 */
public void
cb_reward(object attacker, int dam, int kill)
{
    int tmp, j, align, size;
    object *share;

    if (!kill)
    {
	attacker->add_exp(dam, 1);
	return;
    }

    tmp = F_KILL_GIVE_EXP(me->query_average_stat());
    if (me->query_npc())
	tmp = me->query_exp_factor() * tmp / 100;

    share = ({ attacker });

    /*
     * Let the team share the xp
     */
    if (attacker->query_leader())	/* Find my leader and mates */
	    share = share + attacker->query_leader()->query_team() +
		({ attacker->query_leader() });

    else if (attacker->query_team())	/* Find members of my team */
    {
	share = share + (object*)attacker->query_team();
    }

    /*
     * Only present members get their share.
     */
    share = share & all_inventory(environment(me));

    j = -1;
    size = sizeof(share);
    while(++j < size)
    {
	share[j]->add_exp(tmp / sizeof(share), 1);
    }

    /*
     * Change the alignment of the killer
     */
    attacker->set_alignment((align = attacker->query_alignment()) +
        F_KILL_ADJUST_ALIGN(align, me->query_alignment()));
}

/*
 * Function name: cb_death_occured
 * Description:   Called when 'me' dies
 * Arguments:     killer: The enemy that caused our death.
 */
public void
cb_death_occured(object killer)
{
    int il, size;
    object *tm;

    /*
     * Tell everyone the bad (good) news.
     */
    tell_room(environment(me), QCTNAME(me) + " died.\n", me);
    tell_object(killer, "You killed " + me->query_the_name(killer) + ".\n");

    /*
     * We forget our enemies when we die.
     */
    remove_call_out("heart_beat");
    enemies = ({});
    attack_ob = 0;
    
    /*
     * Reward for kill (den enes d|d, den andres br|d)
     */
    cb_reward(killer, 0, 1);

    /* 
     * Adjust panic values
     */
    killer->add_panic(-25); /* Killing the enemy reduces panic */
    tm = (object*)killer->query_team_others();
    il = -1;
    size = sizeof(tm);
    while(++il < size)
    {
	if (environment(killer) == environment(tm[il]))
	{
	    tm[il]->add_panic(-15);
	}
    }

    tm = (object*)me->query_team_others();
    il = -1;
    size = sizeof(tm);
    while(++il < size)
    {
	if (environment(me) == environment(tm[il]))
	{
	    tm[il]->add_panic(25);
	}
    }
}

/*
 * Function name: cb_add_enemy
 * Description:   Used to add enemies to 'me'
 * Arguments:     enemy: The enemy to be
 *                force: If true and enemy array full one other is replaced
 */
public varargs void
cb_add_enemy(object enemy, int force)
{
    int pos;
    enemies = enemies - ({ 0 });
  /* Make sure panic value is updated before we add enemies */
    cb_query_panic(); 
    pos = member_array(enemy, enemies);

    if (force && pos >= 0)
	enemies = ({enemy}) + exclude_array(enemies, pos, pos);
    else if (force)
	enemies = ({ enemy }) + enemies;
    else if (pos < 0)
	enemies = enemies + ({ enemy });

    if (sizeof(enemies) > MAX_ENEMIES)
	enemies = slice_array(enemies, 0, MAX_ENEMIES - 1);
}

/*
 * Function name: cb_adjust_combat_on_move
 * Description:   Called to let movement affect the ongoing fight. This
 *                is used to print hunting messages or drag enemies along.
 * Arguments:	  True if leaving else arriving
 */
public void 
cb_adjust_combat_on_move(int leave)
{
    int i, pos, size;
    object *inv, enemy, *all, *rest, *drag;

    if (environment(me))
    {
	all = all_inventory(environment(me));
	inv = all & enemies;
	if (leave)
        {
	    /*
	     * If the aggressors are around.
	     */
	    if (sizeof(inv))
	    {
		drag = ({ });
		rest = ({ });
		i = -1;
		size = sizeof(inv);
		while(++i < size)
		{
		    if (inv[i]->query_prop(LIVE_O_ENEMY_CLING) == me)
		    {
			drag += ({ inv[i] });
			tell_object(inv[i], "As " +
			    me->query_the_name(inv[i]) + 
			    " leaves, you are dragged along.\n");
		    }
		    else
		    {
			rest += ({ inv[i] });
			tell_object(inv[i], "You are now hunting " +
			    me->query_the_name(inv[i]) + ".\n");
		    }
		}

		if (sizeof(drag))
		{
		    if (i_see_combat)
		    {
			me->catch_msg(
			    "As you try leave, you can not get rid of " +
			    COMPOSITE_LIVE(drag) + ".\n");
		    }
		    me->add_prop(TEMP_DRAGGED_ENEMIES, drag);
		}

		if (sizeof(rest) && i_see_combat)
		{
		    me->catch_msg("You are now hunted by " + 
			COMPOSITE_LIVE(rest) + ".\n");
		}

		/* Stop fighting all the enemies that don't follow us.
                   We must still fight the enemies that do, since otherwise
                   we can move so quickly that we don't update our enemies
                   to include them when they attack again, although they
                   will autofollow and attack again on entry.
                */
		this_object()->cb_stop_fight(rest);
	    }
    	} 
	else 
	{
	    i = -1;
	    size = sizeof(inv);
	    while(++i < size)
	    {
		if (!NPATTACK(inv[i]) && CAN_SEE(me, inv[i]))
		{
		    me->reveal_me(1);
		    inv[i]->reveal_me(1);
		    cb_attack(inv[i]);
		    cb_update_tohit_val(inv[i], 30); /* Give hunter bonus */
		    tell_room(environment(me), QCTNAME(me) + " attacks " +
                        QTNAME(inv[i]) + ".\n", ({ inv[i], me }));
                    tell_object(inv[i], me->query_The_name(inv[i]) +
			" attacks you!\n");
                    tell_object(me, "You attack " + inv[i]->query_the_name(me) +
			".\n");
		    me->reveal_me(1);
	        }
	    }
	}
    }
}

/*
 * Function name: cb_run_away
 * Description:   'me' runs away from the fight
 * Arguments:     dir: The first dir tried
 */
public void
cb_run_away(string dir)
{
    object          here;
    int             size, pos,
		    i,
                    j;
    mixed	    *exits;
    string	    *std_exits;


    if (me->query_ghost() ||
		(me->query_npc() && me->query_prop(NPC_I_NO_RUN_AWAY)))
	return;

    here = environment(me);
    i = 0;
    std_exits = ({ "north", "south", "west", "east", "up", "down" });
    if (stringp(dir))
	me->command(dir);

    exits = here->query_exit();
    size = sizeof(exits);
    j = random(size / 3);

    while (i < size && here == environment(me))
    {
	i += 3;
	if ((pos = member_array(exits[j * 3 + 1], std_exits)) > -1)
	    std_exits[pos] = "";
	me->command(exits[j * 3 + 1]);
	j++;
	if (j * 3 >= size)
	    j = 0;
    }

    size = sizeof(std_exits);
    j = random(size);
    i = 0;
    while (i < size && here == environment(me))
    {
	i++;
	if (strlen(std_exits[j]))
	    me->command(std_exits[j]);
	j++;
	if (j >= size)
	    j = 0;
    }

    if (here == environment(me))
    {
	tell_room(environment(me),
		  QCTNAME(me) + " tried, but failed to run away.\n", me);

	tell_object(me,
		    "Your legs tried to run away, but failed.\n");
    }
    else
    {
	tell_object(me, "Your legs run away with you!\n");
    }
}

/*
 * Function name: cb_wield_weapon
 * Description:   Wield a weapon. 'Weapon' is here a general term for any tool
 *                used as a weapon. Only players are limited to /std/weapon
 *		  weapons.
 * Arguments:	  wep - The weapon to wield.
 * Returns:       True if wielded.
 */
public mixed
cb_wield_weapon(object wep) 
{ 
    return ""; 
}

/*
 * Function name: cb_show_wielded
 * Description:   Describe the currently wielded weapons.
 * Argumensts:    ob: The object to give the description
 * Returns:       Description string.
 */
public string 
cb_show_wielded(object ob) 
{ 
    return ""; 
}

/*
 * Function name: unwield
 * Description:   Unwield a weapon.
 * Arguments:	  wep - The weapon to unwield.
 * Returns:       None.
 */
public void
cb_unwield(object wep) 
{
}

/*
 * Function name: cb_query_weapon
 * Description:   Returns the weapon held in a specified location.
 *		  A list of all if argument -1 is given.
 * Arguments:	  which: A numeric label describing a weapon
 *                       location. On humanoids this is W_RIGHT etc.
 * Returns:       The corresponding weapon.
 */
public mixed
cb_query_weapon(int which)
{
    if (which == -1)
	return ({});
    else
	return 0; 
}

/*
 * Function name: cb_wear_arm
 * Description:   Wear an armour
 * Arguments:	  arm - The armour.
 */
public int
cb_wear_arm(object arm) 
{ 
    return 0; 
}

/*
 * Function name: cb_show_worn
 * Description:   Describe the currently worn armours
 * Argumensts:    ob: The object to give the description
 * Returns:       Description string.
 */
public string
cb_show_worn(object ob) 
{ 
    return ""; 
}

/*
 * Function name: cb_remove_arm
 * Description:   Remove an armour
 * Arguments:	  arm - The armour.
 */
public void
cb_remove_arm(object arm) 
{
}

/*
 * Function name: cb_query_armour
 * Description:   Returns the armour of a given position.
 *		  A list of all if argument -1 is given.
 * Arguments:	  which: A numeric label describing an armour
 *                       location. On humanoids this is TS_HEAD etc.
 * Returns:       The corresponding armour
 */
public mixed
cb_query_armour(int which)
{
    if (which == -1)
	return ({});
    else
	return 0; 
}

public void
cb_update_speed()
{
    int i;
    if (me) i = me->query_prop(LIVE_I_QUICKNESS);
    speed = 5.0 - (itof(i) / 50.0);
}

/***********************************************************
 * The non redefinable functions follows below
 */

static void
restart_heart()
{
    if (!alarm_id || !get_alarm(alarm_id))
    {
        cb_update_speed();
        alarm_id = set_alarm(speed, speed, "heart_beat");
    }
}

static void
stop_heart()
{
    remove_alarm(alarm_id);
}

/*
 * Function name: heart_beat
 * Description:   Do 1 round of fighting with the choosen enemy. This is
 *                done as long as both me and enemy is alive and in the
 *                same place.
 */
static nomask void
heart_beat()
{
    int             il, dt, hitsuc, tmp, size;
    mixed	    *hitresult, *dbits, pen, fail;
    object          *new, ob;
    
    if (!objectp(me) || me->query_ghost())
    {
	attack_ob = 0;
	stop_heart();
	return;
    }

    /*
     * Do something when the enemy is somehow lost
     */
    if (!attack_ob || attack_ob->query_ghost() ||
	environment(attack_ob) != environment(me))
    {
	me->notify_enemy_gone(attack_ob);

	/*
         * To cling to an enemy we must fight it.
         */
	remove_prop(LIVE_O_ENEMY_CLING);
	    
	/*
	 * Switch enemy if we have an alternate
	 */
	enemies = enemies - ({ 0 });
	new = (all_inventory(environment(me)) & enemies) - ({ attack_ob });

	if (sizeof(new))
	    attack_ob = new[0];
	else {
	    if (attack_ob && attack_ob->query_ghost())
	    {
		me->remove_prop(LIVE_I_ATTACK_DELAY);
		me->remove_prop(LIVE_I_STUNNED);
	    }
	    attack_ob = 0;
	}

        /*
         * We attack another enemy when old enemy left.
	 */
	if (attack_ob)
	{
	    tell_object(me, "You turn to attack " +
		attack_ob->query_the_name(me) + ".\n");
	    heart_beat();
	    return;
	}
	else
	{
	    stop_heart();
	    return;
	}
    }

    /* 
     * The enemy is still here, run through our attacks
     */

    /* First do some check if we actually attack
    */
    if (pointerp(fail = me->query_prop(LIVE_AS_ATTACK_FUMBLE)) &&
	sizeof(fail))
    {
	if (i_see_combat)
	{
	    me->catch_msg(fail[0]);
	}
	return;
    }

    if ((tmp = me->query_prop(LIVE_I_ATTACK_DELAY)))
    {
	if ((tmp -= ftoi(speed)) > 0)
	{
	    me->add_prop(LIVE_I_ATTACK_DELAY, tmp);
	    return;
	}
	else
	    me->remove_prop(LIVE_I_ATTACK_DELAY);
    }

#if 0
    if (((hit_heart * 100) + me->query_prop(LIVE_I_QUICKNESS)) < random(100))
    	return 1; /* Wait one round more then. */
    hit_heart = -1;
#endif

    if (me->query_prop(LIVE_I_STUNNED))
        return;

    /*
        This is a hook for NPC's so that they can do spells or any
        special actions when in combat. See /std/mobile.c
    */
    if (me->query_npc() && me->special_attack(attack_ob))
        return;

    /*
	This is the hook for single special attacks, normally spells,
        that is done instead of the normal attacks, one turn.
    */
    if (objectp(ob = me->query_prop(LIVE_O_SPELL_ATTACK)))
    {
	ob->spell_attack(me, attack_ob);
	me->remove_prop(LIVE_O_SPELL_ATTACK);
	return;
    }

    if (me->query_prop(LIVE_I_CONCENTRATE))
        return;

    il = -1;
    size = sizeof(attacks);
    while(++il < size)
    {
    	/*
	 * Will we use this attack this round? (random(100) < %use)
	 */
    	if (random(100) < attacks[il][ATT_PROCU])
    	{
	    /*
	     * The attack has a chance of failing. If for example the attack
	     * comes from a wielded weapon, the weapon can force a fail or
	     * if the wchit is to low for this opponent.
	     */

	    hitsuc = cb_try_hit(att_id[il]);
	    if (hitsuc <= 0)
		continue;

	   /* 
	    * The intended victim can also force a fail. like in the weapon
	    * case, if fail, the cause must produce explanatory text himself.
	    */

	    hitsuc = attack_ob->query_not_attack_me(me, att_id[il]);
	    if (hitsuc > 0)
		continue;

	    hitsuc = cb_tohit(att_id[il], attacks[il][ATT_WCHIT], attack_ob);
	
	    if (hitsuc > 0)
	    {
	    	/* Choose one damage type
                 */
	    	if (!random(2500))
		{
		    // Critical hit!
		    if (random(10))
		    {
			pen = attacks[il][ATT_M_PEN];
			if (sizeof(pen))
			    pen = pen[0];
			pen *= 5;
		    }
		    else	
			pen = attack_ob->query_hp() + me->query_hp();
		    dt = -1;
		}
		else
		{
		    dt = attacks[il][ATT_DAMT];
		    dbits = 
			({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON }) - ({0});
		    dt = dbits[random(sizeof(dbits))];
		    
		    pen = attacks[il][ATT_M_PEN];
		    if (sizeof(pen))
		    {
			tmp = MATH_FILE->quick_find_exp(dt);
			if((tmp < sizeof(pen)))
			    pen = pen[tmp];
			else
			    pen = pen[0];
		    }
		}

	    	hitresult = (mixed*)attack_ob->hit_me(
		    pen,
		    dt,
		    me, att_id[il]);
	    }
	    else
	        hitresult = 
		    (mixed*)attack_ob->hit_me(hitsuc, 0, me, att_id[il]);
	
	    /*
	     * Generate combat message, arguments Attack id, hitloc description
	     * proc_hurt, Defender
	     */
	    if (hitsuc > 0)
	    {
		/* A small patch to track a bug. */
                if (!intp(tmp) || tmp < 0)
                    {
                        log_file("BAD_TMP", file_name(this_object()) + "  " +
                                 file_name(me) + "  " + me->query_name() +
                                 "\n" + cb_status());
                        tmp = 0;
                    }
		
	    	hitsuc = attacks[il][ATT_WCPEN][tmp];
	    	if (hitsuc > 0)
		    hitsuc = 100 * hitresult[2] / hitsuc;
	    	else
		    hitsuc = 0;
	    }
	    if (hitresult[1])
	    	cb_did_hit(att_id[il], hitresult[1], hitresult[0], 
		       attack_ob, dt, hitsuc, hitresult[3]);
	    else
	        break; /* Ghost, linkdeath, immortals etc */
	
	    /*
	     * Ooops, Lifeform turned into a deadform. Reward the killer.
	     */
	    if ((int)attack_ob->query_hp() <= 0)
	    {
	        enemies = enemies - ({ attack_ob });
	        attack_ob->do_die(me);
	        break;
	    }
    	}
    }

    /*
     * Fighting is quite tiresome you know
     */
    if (me->query_fatigue())
    	me->add_fatigue(-1);
    else
    {
    	tell_object(me,
		"You are so tired that every move drains your health.\n");
    	me->reduce_hit_point(1);
    }

    /*
     * Fighting is frightening, we might panic!
     */
    cb_may_panic();

    if (attack_ob && !attack_ob->query_ghost())
    	return;
    else
    {
    	new = (all_inventory(environment(me)) & enemies) - ({ attack_ob });
    	if (sizeof(new))
    	{
	    attack_ob = new[0];
	    if (attack_ob)
	        tell_object(attack_ob, "You turn to attack " +
		    attack_ob->query_the_name(me) + ".\n");
        }
    	else
    	{
	    me->remove_prop(LIVE_I_ATTACK_DELAY, 0);
	    attack_ob = 0;
	    stop_heart();
	    return;
    	}
    }
    return;
}


/*
 * Function name: cb_hit_me
 * Description:   Called to decide damage for a certain hit on 'me'.
 * Arguments:	  wcpen:     Weapon class penetration
 *                dt:        Damage type, MAGIC_DT if no ac helps
 *                attacker: 
 *                attack_id: -1 if a special attack
 * Returns:       Result of hit: ({ proc_hurt, hitloc description, phit, dam })
 */
public nomask mixed
cb_hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object      *list;
    int		proc_hurt, hp,
    		tmp, dam, phit,
    		hloc,
    		j, size;
    string      msg;
    mixed	ac;
    
    if (!objectp(me))
    {
	cb_link();
    }
    
    /*
     * You can not hurt the dead.
     */
    if (me->query_ghost())
    {
	tell_object(attacker, me->query_The_name(attacker) +
	    " is a already dead, quite dead.\n");
	tell_room(environment(me),
		  QCTNAME(attacker) + " is trying to kill the already dead.\n",
		  attacker);
	tell_object(me, attacker->query_The_name(me) +
	    " tries futily to attack you.\n");
	me->stop_fight(attacker);
	attacker->stop_fight(me);
	return ({ 0, 0, 0, 0});
    }

    /*
     * Update the list of aggressors. If we hit ourselves: no update. 
     */
    cb_add_enemy(attacker);
    if (!attack_ob && attacker != me) 
	attack_ob = attacker;
    restart_heart();

    /*
     * Choose a hit location, and compute damage if wcpen > 0
     */
    tmp = random(100);
    j = 0;
    hloc = -1;
    size = sizeof(hitloc_ac);

    if (!size)
    {
	log_file("NO_HITLOC", me->query_real_name() + " (" + file_name(me) +
		 "): " + file_name(this_object()) + "\n");
	me->stop_fight(attacker);
	attacker->stop_fight(me);
	return ({ 0, 0, 0, 0});
    }
	
    while(++hloc < size)
    {
	j += hitloc_ac[hloc][HIT_PHIT];
	if (j >= tmp)
	    break;
    }

    if (hloc >= sizeof(hitloc_ac))
    {
	hloc = sizeof(hitloc_ac) - 1;
/*	log_file("BAD_HITLOC", me->query_real_name() + " (" + file_name(me) +
		 "): " + file_name(this_object()) + "\n");
		 */
    }

    ac = hitloc_ac[hloc][HIT_M_AC];
    
    if (wcpen > 0)
    {
	if (dt == MAGIC_DT)
	    ac = 0;
	else
	{
	    tmp = (int)MATH_FILE->quick_find_exp(dt);
	
	    if (sizeof(ac) && (tmp < sizeof(ac)))
	        ac = ac[tmp];
	    else if (sizeof(ac))
	        ac = ac[0];
	    else if (!intp(ac))
	        ac = 0;
	}

	phit = random(wcpen);
 	ac = random(ac);
	dam = F_DAMAGE(phit, ac);
	if (dam < 1)
	    dam = 0;
    }
    else
    {
	dam = 0;
	phit = (wcpen < 0 ? wcpen : -1);
    }

    hp = me->query_hp();

    /*
     * Wizards are immortal. (immorale ??)
     */
    if ((int)me->query_wiz_level() && dam >= hp)
    {
	tell_object(me, "Your wizardhood protects you from death.\n");
	tell_room(environment(me),
		  QCTNAME(me) + " is immortal and fails to die!\n", me);
	return ({ 0, 0, 0, 0 });
    }
    
    /*
     * Ok, hurt me.
     */
    if (dam > 0 && hp)
    {
        proc_hurt = (100 * dam) / hp;
	if (dam && !proc_hurt)
	    proc_hurt = 1;     /* Less than 1% damage */
    }
    else if (dam > 0)
	proc_hurt = 100;
    else if (wcpen >= 0)
        proc_hurt = 0;
    else
	proc_hurt = -1;   /* Enemy missed */
    
    if (dam > 0)
	me->heal_hp(-dam);
    
    /*
     * Adjust our panic level
     */
    if (proc_hurt >= 0)
	cb_add_panic(2 + proc_hurt / 5);
    
    /*
     * Tell us where we were attacked and by which damagetype
     */
    cb_got_hit(hit_id[hloc], proc_hurt, attacker, attack_id, dt, dam);
    
    /*
     * Reward attacker for hurting me
     */
    if (dam)
    {
#ifdef CB_HIT_REWARD
	cb_reward(attacker, dam, 0);
#endif
	if (random(dam) > random(me->query_stat(SS_DIS)))
	    me->cmdhooks_break_spell();
    }
    
    return ({ proc_hurt, hitloc_ac[hloc][HIT_DESC], phit, dam });
}

/*
 * Function name: cb_attack
 * Description:   Called by the internal combat routines to attack.
 * Arguments:     victim: The object of the attack                
 */
public nomask void
cb_attack(object victim)
{
    if (!me)
	return;
    
    restart_heart();
    
    if (victim == me || victim == attack_ob || victim->query_ghost())
	return;

    me->reveal_me(1);
    victim->reveal_me(1);
    /*
     * Swap attack
     */
    cb_add_enemy(victim, 1);
    attack_ob = victim;

    this_player()->reveal_me(1);
    victim->reveal_me(1);
    victim->attacked_by(me);
}

/*
 * Function name:  cb_attacked_by
 * Description:    This routine is called when we are attacked or when 
 *                 someone we are hunting appears in our location.
 * Arguments:	   ob: The attacker
 */
public nomask void
cb_attacked_by(object ob)
{
    cb_add_enemy(ob);
    
    if (!attack_ob || (!query_ip_number(attack_ob) && query_ip_number(ob)))
	attack_ob = ob;
    
    restart_heart();

    if (me)
	me->cr_attacked_by(ob);
}

/*
 * Function name: cb_stop_fight
 * Description:   Stop fighting certain enemies
 */
public nomask /* void */
cb_stop_fight(mixed elist)
{
    if (objectp(elist))
	elist = ({ elist });
    else if (!pointerp(elist))
	elist = ({});
    
    if (member_array(attack_ob, elist) >= 0)
	attack_ob = 0;
    
    if (pointerp(enemies) && pointerp(elist))
	enemies = enemies - elist;
    
    if (sizeof(enemies))
	attack_ob = enemies[0];
}

/*
 * Function name: cb_query_enemy
 * Description:   Gives our current enemy
 * Arguments:     arg: Enemy number, (-1 == all enemies)
 * Returns:       Object pointer to the enemy
 */
public nomask mixed
cb_query_enemy(int arg)
{
    enemies = enemies - ({ 0 });
    if (arg == -1)
	return enemies + ({});
    else if (arg < sizeof(enemies))
	return enemies[arg];
    else 
	return 0;
}

/*
 * Function name: cb_query_attack_ob
 * Description:   Gives the enemy we are fighting, if we are fighting...
 * Returns:       Object pointer to the enemy
 */
public nomask mixed
cb_query_attack() 
{ 
    return attack_ob; 
}

/*
 * Function name:  cb_heal
 * Description:    Heals the living object. Adds hp, mana and fatigue, panic
 * Arguments:	   delay: Number of heart_beats since last heal
 * Returns:        0 if we healed 'me'
 */
public nomask int
cb_heal(int delay)
{
    return 0;
}

/**********************************************************
 * 
 * Below is internal functions, only used by the inheritor of
 * this standard combat object.
 */

/*
 * Function name: add_attack
 * Description:   Add an attack to the attack array.
 * Arguments:	  
 *             wchit: Weapon class to hit
 *             wcpen: Weapon class penetration
 *	       dt:    Damage type
 *             %use:  Chance of use each turn
 *	       id:    Specific id, for humanoids W_NONE, W_RIGHT etc
 *	       skill: Optional skill with this attack
 *
 * Returns:       True if added.
 */
static varargs int
add_attack(int wchit, mixed wcpen, int damtype, int prcuse, int id, int skill)
{
    int pos, *pen, *m_pen;

    if (sizeof(attacks) >= MAX_ATTACK)
	return 0;

    pen = allocate(W_NO_DT);
    m_pen = allocate(W_NO_DT);

    if (skill == 0)
        skill = wchit;
    else if (skill < 1)
        skill = 0;

    pos = -1;
    while(++pos < W_NO_DT)
    {
  	if (!pointerp(wcpen))
	{
	    m_pen[pos] = F_PENMOD(wcpen, skill);
	    pen[pos] = wcpen;
	}
	else if (pos >= sizeof(wcpen))
	{
	    m_pen[pos] = (pos ? m_pen[0] : 0);
	    pen[pos] = (pos ? pen[0] : 0);
	}
	else
	{
	    m_pen[pos] = F_PENMOD(wcpen[pos], skill);
	    pen[pos] = wcpen[pos];
	}
    }

    if ((pos = member_array(id, att_id)) < 0)
    {
	att_id += ({ id });
	attacks += ({ ({ wchit, pen, damtype, prcuse, skill, m_pen }) });
	return 1;
    }
    else
	attacks[pos] = ({ wchit, pen, damtype, prcuse, skill, m_pen });
    
    return 1;
}

/*
 * Function name: remove_attack
 * Description:   Removes a specific attack
 * Arguments:     id: The attack id
 * Returns:       True if removed
 */
static int
remove_attack(int id) 
{
    int pos;
    
    if ((pos = member_array(id, att_id)) >= 0)
    {
	attacks = exclude_array(attacks, pos, pos);
	att_id = exclude_array(att_id, pos, pos);
	return 1;
    }
    return 0;
}

/*
 * Function name: query_attack_id
 * Description:   Give all attack id's
 * Returns:       Array with elements as described in add_attack
 */
public int *
query_attack_id() 
{ 
    return att_id + ({}); 
}

/*
 * Function name: query_attack
 * Description:   Give the attack for a certain id
 * Arguments:     id: The id to return attack array for
 * Returns:       Array with elements as described in add_attack
 */
public mixed *
query_attack(int id) 
{
    int pos;
    
    if ((pos = member_array(id, att_id)) >= 0)
    {
	return attacks[pos];
    }
    return 0;
}

/*
 * Function name: add_hitloc
 * Description:   Add a hitlocation to the hitloc array
 * Arguments:	  
 *	      ac:    The ac's for a given hitlocation, can be an int
 *	      %hit:  The chance that a hit will hit this location
 *	      desc:  String describing this hitlocation, ie "head", "tail"
 *	      id:    Specific id, for humanoids A_TORSO, A_HEAD etc
 *
 * Returns:       True if added.
 */
static int
add_hitloc(mixed ac, int prchit, string desc, int id)
{
    int pos, *act, *m_act;

    if (sizeof(hitloc_ac) >= MAX_HITLOC)
	return 0;
    
    act = allocate(W_NO_DT);
    m_act = allocate(W_NO_DT);

    pos = -1;
    while(++pos < W_NO_DT)
    {
	if (!pointerp(ac))
    	{
	    m_act[pos] = F_AC_MOD(ac);
	    act[pos] = ac;
	}
	else if (pos >= sizeof(ac))
	{
	    act[pos] = (pos ? act[0] : 0);
	    m_act[pos] = (pos ? F_AC_MOD(act[0]) : 0);
	}
	else
	{
	    m_act[pos] = F_AC_MOD(ac[pos]);
	    act[pos] = ac[pos];
	}
    }
    if ((pos = member_array(id, hit_id)) < 0)
    {
	hit_id += ({ id });
	hitloc_ac += ({ ({ act, prchit, desc, m_act }) });
    }
    else
	hitloc_ac[pos] = ({ act, prchit, desc, m_act });
    
    return 1;
}

/*
 * Function name: remove_hitloc
 * Description:   Removes a specific hit location
 * Arguments:     id: The hitloc id
 * Returns:       True if removed
 */
static int
remove_hitloc(int id) 
{
    int pos;
    
    if ((pos = member_array(id, hit_id)) >= 0)
    {
	hitloc_ac = exclude_array(hitloc_ac, pos, pos);
	hit_id = exclude_array(hit_id, pos, pos);
	return 1;
    }
    return 0;
}

/*
 * Function name: query_hitloc_id
 * Description:   Give all hitloc id's
 * Returns:       Array with elements as described in add_attack
 */
public int *
query_hitloc_id() 
{ 
    return hit_id + ({}); 
}

/*
 * Function name: query_hitloc
 * Description:   Give the hitloc for a certain id
 * Arguments:     id: The id to return hitloc array for
 * Returns:       Array with elements as described in add_hitloc
 */
public nomask mixed *
query_hitloc(int id) 
{
    int pos;
    
    if ((pos = member_array(id, hit_id)) >= 0)
    {
	return hitloc_ac[pos];
    }
    return 0;
}

/*
 * Function name: 
 * Description:   
 * Arguments:	  
 * Returns:       
 */
