/*
 * This is the steed proper.  The steed will age, and also, upon reaching
 * old age, die.
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

/*
 * We use some stuff from here
 */
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <living_desc.h>
#include <math.h>
#include <tasks.h>
#include <state_desc.h>
#include "/std/combat/combat.h"
#include "steed.h"

/*
 * Symbolic names for the attacks and hitlocs
 */
#define	A_BITE	0
#define	A_KICK	1

#define	H_HEAD	0
#define	H_NECK	1
#define	H_BODY	2
#define	H_FEET	3

/*
 * Sublocation identifier for rider
 */
#define	RIDING_SUBLOC	"_subloc_riding"

/*
 * Get to the combat object
 */
#define	CEX	if (!combat_extern) combat_reload()

/*
 * Information we need to keep around
 */
string owner, my_long, gItem;
int age, max_age, force_env, hit_rider;
mapping command_map;

static int fatigue_time, stuffed_time;
static int last_stuffed;
private int stuffed;

void
create_steed()
{
    set_name("steed");
    set_race_name("steed");
    set_adj("unconfigured");
}

/*
 * Function name: create_creature
 * Description:   Set up default values for the steed
 */
nomask void
create_creature()
{
    /*
     * If this is the master object, don't do anything
     */
    if (!IS_CLONE)
	return;

    /*
     * Default values for names, adjectives and description.  The long desc is
     * in a seperate function if mounted!
     */
    ::set_long("@@long_desc@@");

    my_long = "This is a rather unconfigured steed.";

    /*
     * Set up the steeds default stats (will be overridden)
     */
    set_stats( ({ 1, 1, 1, 1, 1, 1 }) );

    /*
     * Make sure our stats improve with gained experience
     */
    set_learn_pref( ({ 17, 17, 17, 16, 16, 17 }) );

    /*
     * And heal fully
     */
    set_hp(query_max_hp());

    /*
     * We need some properties as well
     */
    add_prop(CONT_I_LIGHT, "@@light_value@@");
    add_prop(NPC_I_NO_LOOKS, 1);

    /*
     * Let us give it some default skills (will be overridden)
     */
    set_skill(SS_DEFENCE, 1);
    set_skill(SS_UNARM_COMBAT, 1);
    set_skill(SS_AWARENESS, 1);

    /*
     * And some attacks as well (values need fixing)
     */
    set_attack_unarmed(A_BITE, 1, 1, W_IMPALE, 20, "bite");
    set_attack_unarmed(A_KICK, 1, 1, W_BLUDGEON, 80, "kick");

    /*
     * And put in some hitlocs fitting a steed (values need fixing)
     */
    set_hitloc_unarmed(H_HEAD, ({ 1, 1, 1, 1 }), 15, "head");
    set_hitloc_unarmed(H_NECK, ({ 1, 1, 1, 1 }), 10, "neck");
    set_hitloc_unarmed(H_BODY, ({ 1, 1, 1, 1 }), 65, "body");
    set_hitloc_unarmed(H_FEET, ({ 1, 1, 1, 1 }), 10, "feet");

    /*
     * Set up the commands we need to handle for mounted players.
     * The directional commands are here to make sure we handle
     * doors properly.
     */
    command_map = ([
		     "enter"     : "do_dir",
		     "north"     : "do_dir",
		     "south"     : "do_dir",
		     "west"      : "do_dir",
		     "east"      : "do_dir",
		     "northwest" : "do_dir",
		     "northeast" : "do_dir",
		     "southwest" : "do_dir",
		     "southeast" : "do_dir",
		     "up"        : "do_dir",
		     "down"      : "do_dir",
		     "dismount"  : "do_dismount",
		     "kill"      : "do_charge",
		     "look"      : "do_look",
		     "exa"       : "do_look",
		     "examine"   : "do_look",
		     "join"      : "do_join",
		     "leave"     : "do_leave",
		     "invite"    : "do_invite"
		  ]);

    stuffed_time = fatigue_time = time();

    call_out("check_age", CHECK_TIME);

    create_steed();
}

/*
 * Function name: do_charge
 * Description:   Allow attacks from the back of the steed
 * Arguments:     arg - the rest of the command string
 * Returns:       1 - successful
 *                0 - not successful
 */
int
do_charge(string arg)
{
    object ob, save;

    notify_fail("Kill what?\n");
    if (!arg)
	return 0;
    ob = present(arg, environment());
    notify_fail("Kill whom?\n");
    if (!ob || ob == this_object())
	return 0;
    if (!F_DARE_ATTACK(this_player(), ob)) {
	write("Um, no, you don't dare.\n");
	return 1;
    }
    if (!CAN_SEE(this_object(), ob) || !CAN_SEE_IN_ROOM(this_object())) {
	write("You cannot see to do that.\n");
	return 1;
    }
    this_player()->catch_msg("You charge " +
			     (this_player()->query_met(ob) ?
			     	ob->query_met_name() : ob->query_nonmet_name()) +
			     ".\n");
    ob->catch_msg((ob->query_met(this_player()) ? METNAME : NONMETNAME) +
		  " charges you on " + QTNAME(this_object()) + ".\n");
    tell_room(environment(), QCTNAME(this_player()) + " charges "+
	      QTNAME(ob) + " from " + QTNAME(this_object()) + ".\n",
	      ({ this_player(), this_object(), ob }));
    save = this_player();
    set_this_player(this_object());
    attack_object(ob);
    set_this_player(save);
    return 1;
}

/*
 * Function name: tell_watcher
 * Description:   Send the string fromthe fight to people that want them
 * Arguments:     str   - the string to send
 *                enemy - the enemy being hit
 */
static void
tell_watcher(string str, object enemy)
{
    object *ob;
    int i;

    ob = FILTER_LIVE(all_inventory(environment())) - ({ this_object() });
    ob -= ({ enemy });
    for (i=0 ; i<sizeof(ob) ; i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}

/*
 * Function name: special_attack
 * Description:   Called from the combat object do override the
 *                attacks. We use it to be able to let the rider
 *                actually do the fighting. Most of this code is
 *                copied from the standard combat object.
 * Arguments:     victim - the object we are currently fighting
 * Returns:       0 - proceed with a normal attack
 *                1 - we did the attack here
 */
nomask int
special_attack(object victim)
{
    object rider, cbobj, *new, ob, *enemies;
    mixed attacks, *hitresult, *dbits, *pen, fail;
    int il, *att_ids, dt, hitsuc, tmp;
    string where, with, how, what, owhat;

    rider = find_player(owner);
    if (!rider || environment(rider) != this_object())
	return 0;
    cbobj = rider->query_combat_object();
    if (objectp(ob = rider->query_prop(LIVE_O_SPELL_ATTACK))) {
	ob->spell_attack(rider, victim);
	rider->remove_prop(LIVE_O_SPELL_ATTACK);
	return 1;
    }
    fail = query_enemy(-1);
    enemies = fail;
    att_ids = cbobj->query_attack_id();
    attacks = ({});
    /*
     * Make sure only hitlocs with specific weapon types wielded
     * will be used to hit with.  Also allow the rider to use feet
     * to kick with
     */
    for (il = 0 ; il < sizeof(att_ids) ; il++) {
	ob = rider->query_weapon(att_ids[il]);
	if ((!ob && member_array(att_ids[il], ({ W_FOOTR, W_FOOTL })) >= 0) ||
	    (ob && member_array(ob->query_wt(),
			       ({ W_SWORD, W_POLEARM, W_AXE,
				  W_CLUB, W_MISSILE, W_JAVELIN })) >= 0))
	    attacks += ({ cbobj->query_attack(att_ids[il]) });
    }
    for (il = 0; il < sizeof(attacks); il++)
    {
    	/*
	 * Will we use this attack this round? (random(100) < %use)
	 */
	attacks[il][ATT_SKILL] = attacks[il][ATT_SKILL] *
				 rider->query_skill(SS_MOUNTED_COMBAT) / 100;
    	if (random(100) < attacks[il][ATT_PROCU])
    	{
	    /*
	     * The attack has a chance of failing. If for example the attack
	     * comes from a wielded weapon, the weapon can force a fail or
	     * if the wchit is to low for this opponent.
	     */

	    hitsuc = cbobj->cb_try_hit(att_ids[il]);
	    if (hitsuc <= 0)
		continue;

	   /* 
	    * The intended victim can also force a fail. like in the weapon
	    * case, if fail, the cause must produce explanatory text himself.
	    */

	    hitsuc = victim->query_not_attack_me(rider, att_ids[il]);
	    if (hitsuc > 0)
		continue;

	    hitsuc = cbobj->cb_tohit(att_ids[il], attacks[il][ATT_WCHIT], victim);
	
	    if (hitsuc > 0)
	    {
	    	/* Choose one damage type
                 */
	    	dt = attacks[il][ATT_DAMT];
	    	dbits = 
		    ({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON }) - ({0});
	    	dt = dbits[random(sizeof(dbits))];

		tmp = MATH_FILE->find_exp(dt);
	 	pen = attacks[il][ATT_M_PEN];
		if (sizeof(pen) && (tmp < sizeof(pen)))
		    pen = pen[tmp];
		else if (sizeof(pen))
		    pen = pen[0];

	    	hitresult = (mixed*)victim->hit_me(
		    pen,
		    dt,
		    rider, att_ids[il]);
	    }
	    else
	        hitresult = 
		    (mixed*)victim->hit_me(hitsuc, 0, rider, att_ids[il]);
	
	    /*
	     * Generate combat message, arguments Attack id, hitloc description
	     * proc_hurt, Defender
	     */
	    if (hitsuc > 0)
	    {
	    	hitsuc = attacks[il][ATT_WCPEN][tmp];
	    	if (hitsuc > 0)
		    hitsuc = 100 * hitresult[2] / hitsuc;
	    	else
		    hitsuc = 0;
	    }
	    if (hitresult[1]) {
		if (hitresult[0] >= 0)
		    cbobj->cb_add_panic(-3 - hitresult[0] / 5);
		else
		    cbobj->cb_add_panic(1);

		where = "the " + hitresult[1] + " of ";
		with = cbobj->cb_attack_desc(att_ids[il]);

		if (hitresult[1] == -1) {
		    rider->catch_msg("You aim for " + where +
				     (rider->query_met(victim) ?
				        victim->query_met_name() : victim->query_nonmet_name()) +
				     " with your " + with + " but miss.\n");
		    victim->catch_msg(QCTNAME(rider) + " aims for your " +
				      hitresult[1] + " with " +
				      rider->query_possessive() + " " +
				      with + ", but misses.\n");
		    tell_watcher(QCTNAME(rider) + " aims for " + where + QTNAME(victim) +
				 " with " + rider->query_possessive() +
				 " " + with + ", but misses.\n", victim);
		}
		else {
		    how = ", without effect.";
		    what = "hit";
		    owhat = "hits";
		    where = rider->query_met(victim) ?
			    victim->query_met_name() : victim->query_nonmet_name();

		    if (hitresult[0] < 5) {
			how = ".";
			what = "tickle";
			owhat = "tickles";
		    }
		    else if (hitresult[0] < 10) {
			how = ".";
			what = "graze";
			owhat = "grazes";
		    }
		    else if (hitresult[0] < 20) {
			how = ".";
			what = "hurt";
			owhat = "hurtss";
		    }
		    else if (hitresult[0] < 30) {
			how = ", rather bad.";
			what = "hurt";
			owhat = "hurts";
		    }
		    else if (hitresult[0] < 50) {
			how = ", very bad.";
			what = "hurt";
			owhat = "hurts";
		    }
		    else if (hitresult[0] < 70) {
			how = ", very hard.";
			what = "smash";
			owhat = "smashes";
		    }
		    else if (hitresult[0] < 90) {
			how = ", with a bone crushing sound.";
			what = "smash";
			owhat = "smashes";
		    }
		    else {
			how = ".";
			what = "massacre";
			owhat = "massacres";
			where = rider->query_met(victim) ?
			    victim->query_met_name() : victim->query_nonmet_name();
		    }
		    
		    rider->catch_msg("You " + what + " " + where + " with " +
				     "your " + with + how + "\n");
		    victim->catch_msg(QCTNAME(rider) + " " + owhat + " your " +
				      hitresult[1] + " with " +
				      rider->query_possessive() + " " + with +
				      how + "\n");
		    tell_watcher(QCTNAME(rider) + " " + owhat + " the " +
				 hitresult[1] + " of " + QTNAME(victim) +
				 " with " + rider->query_possessive() + " " +
				 with + how + "\n", victim);
		}
	    }
	    else
	        break; /* Ghost, linkdeath, immortals etc */
	
	    /*
	     * Ooops, Lifeform turned into a deadform. Reward the killer.
	     */
	    if ((int)victim->query_hp() <= 0)
	    {
	        enemies = enemies - ({ victim });
	        victim->do_die(rider);
	        break;
	    }
    	}
    }

    /*
     * Fighting is quite tiresome you know
     */
    if (rider->query_fatigue())
    	rider->add_fatigue(-1);
    else
    {
    	tell_object(rider,
		"You are so tired that every move drains your health.\n");
    	rider->reduce_hit_point(1);
    }

    /*
     * Fighting is frightening, we might panic!
     */
    cbobj->cb_may_panic();

    if (!victim || victim->query_ghost())
    {
    	new = (all_inventory(environment(this_object())) & enemies) - ({ victim });
    	if (sizeof(new))
    	{
	    victim = new[0];
	    if (victim)
	        rider->catch_msg("You turn to attack " +
		    QCTNAME(victim) + ".\n");
        }
    	else
    	{
	    rider->remove_prop(LIVE_I_ATTACK_DELAY, 0);
	    victim = 0;
    	}
    }
    return 1;
}

/*
 * Function name: hit_steed
 * Description:   Called to check if the steed or its rider should
 *                take the damage of a hit.  This should be overridden
 *                depending on type of steed, weapon used etc.
 * Arguments:     attacker - the object hurting us
 *                att_id   - the attack identifier
 * Returns:       1 to hit the steed, 0 to hit the rider
 */
int
hit_steed(object attacker, int att_id)
{
    return random(2);
}

/*
 * Function name: query_not_attack_me
 * Description:   Called to check if it is allowed to attack this
 *                object.  Will decide on hitting the rider or the
 *                steed, as well as dealing the blow if hitting the
 *                rider.
 * Arguments:     attacker - the object hurting us
 *                att_id   - the special id saying what attack hit
 *                           us, -1 is special attack
 * Returns:       Wether or not the attack was allowed
 */
int
query_not_attack_me(object attacker, int att_id)
{
    int    dt, hitsuc, tmp;
    mixed  *hitresult, *dbits, *pen, attack;
    object target, rider, com_obj;

    /*
     * will we hit steed or rider?
     */
    hit_rider = 0;

    rider = find_player(owner);
    if (rider && environment(rider) == this_object())
	target = rider; /* we have a rider */

    if (!target || hit_steed(attacker, att_id))
	target = this_object();  /* we hit steed... */
    else
	hit_rider = 1;

    /*
     *  O.K. we are going to hit rider
     */
    if (target != rider && rider->query_not_attack_me(attacker, att_id) > 0)
    {
	hit_rider = 0;
	return 1;   /* rider for some reason cant be hit, message produced */
    }

    /*
     * we need to know combat object and which attack is used
     */
    com_obj = attacker->query_combat_object();
    attack = com_obj->query_attack(att_id);

    /*
     * lets hit the target then - this is copied from heart_beat()
     * at the end we will return 1 and before that we do everything what
     * heart_beat() usually does
     */
    if (!attack)
    {
	hit_rider = 0;
	return 1; /* *sigh*  what else can we do? */
    }

    hitsuc = com_obj->cb_tohit(att_id, attack[ATT_WCHIT], target);
	
    if (hitsuc > 0)
    {
	/*
	 * Choose one damage type
	 */
	dt = attack[ATT_DAMT];
	dbits = ({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON }) - ({0});
	dt = dbits[random(sizeof(dbits))];

	tmp = MATH_FILE->find_exp(dt);
	pen = attack[ATT_M_PEN];
	if (sizeof(pen) && (tmp < sizeof(pen)))
	    pen = pen[tmp];
	else if (sizeof(pen))
	    pen = pen[0];

	hitresult = target->hit_me(pen, dt, attacker, att_id);
    }
    else
	hitresult = target->hit_me(hitsuc, 0, attacker, att_id);
	
    /*
     * Generate combat message, arguments Attack id, hitloc description
     * proc_hurt, Defender
     */
    if (hitsuc > 0)
    {
	hitsuc = attack[ATT_WCPEN][tmp];
	if (hitsuc > 0)
	    hitsuc = 100 * hitresult[2] / hitsuc;
	else
	    hitsuc = 0;
    }
    if (hitresult[1])
	com_obj->cb_did_hit(att_id, hitresult[1], hitresult[0], 
			    target, dt, hitsuc, hitresult[3]);
    else
	return 1; /* Ghost, linkdeath, immortals etc */
	
    /*
     * Ooops, Lifeform turned into a deadform. Reward the killer.
     */
    if (target->query_hp() <= 0)
        target->do_die(attacker);

    /*
     * that's all folks!  rest will do heart_beat() itself
     */
    hit_rider = 0;
    return 1;  
}

/*
 * Function name: hit_me
 * Description:   Called to make damage on this object. The actually
 *                damage made is returned and will be used to change
 *                the score of the attacker. We override it here to
 *                be able to damage the rider.
 * Arguments:     wcpen     - the wc penetration
 *                dt        - the damage type
 *                attacker  - the object hurting us
 *                attack_id - the special id saying what attack hit
 *                            us, -1 is special attack
 * Returns:       The hitresult given by the combat object.
 */
mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object rider;

    rider = find_player(owner);
    if (rider && environment(rider) == this_object())
	if (hit_rider)
	    return rider->hit_me(wcpen, dt, attacker, attack_id);
    return ::hit_me(wcpen, dt, attacker, attack_id);
}

/*
 * Function name: run_away
 * Description:   Run away from the fight (panic)
 */
void
run_away()
{
    object cbobj, enemy, rider;
    mixed enemies;
    int i;

    rider = find_player(owner);
    if (rider && environment(rider) == this_object())
	if (rider->resolve_task(TASK_ROUTINE + 150,
				({ TS_DEX, SS_RIDING })) < 1) {
	    rider->catch_msg("You are thrown off your " + query_race_name() +
			     "!\n");
	    say(QCTNAME(rider) + " is thrown off " + rider->query_possessive()+
		" " + query_race_name() + "!\n", ({ this_object(), rider }));
	    rider->move_living("M", environment(), 1, 1);
	    enemy = query_attack();
	    if (enemy) {
		stop_fight(enemy);
		enemy->stop_fight(this_object());
		this_player()->catch_msg("You attack " + QTNAME(enemy) +
					 ".\n");
	    }
	    enemies = query_enemy(-1);
	    cbobj = this_player()->query_combat_object();
	    for (i=0 ; i<sizeof(enemies) ; i++)
		cbobj->cb_add_enemy(enemies[i], 1);
	    stop_fight(enemies);
	}
    ::run_away();
}

/*
 * Function name: long_desc
 * Description:   VBFC to give the long desc of the steed.
 * Returns:       The long desc.
 */
nomask string
long_desc()
{
    object ob;
    string str;

    str = my_long;
    ob = find_player(owner);
    if (environment(ob) == this_object())
	str += " " + ob->query_The_name(this_player()) + " is mounted "+
	       "on " + query_objective() + ".";
    str += "\n";
    return break_string(str, 76);
}

/*
 * Function name: short
 * Description:   Returns the short description of the steed.  If there
 *                there are someone riding on it, report that.
 * Arguments:     for_obj - The object wanting the description.
 * Returns:       The short desc.
 */
nomask varargs string
short(object for_obj)
{
    string desc;
    object ob;

    if (!for_obj)
	for_obj = this_player();
    if (notmet_me(for_obj))
	desc = this_object()->query_nonmet_name();
    else
	desc = this_object()->query_met_name();
    ob = find_player(owner);
    if (ob && environment(ob) == this_object())
	desc += " mounted by " + ob->short(for_obj);
    return desc;
}

/*
 * Function name: rider_desc
 * Description:   Get a description of a mounted rider.
 * Arguments:     str - the name of the rider.
 * Returns:       The description of the rider.
 */
nomask string
rider_desc(string str)
{
    object ob;

    if (!str)
	return "";
    ob = find_player(str);
    if (ob)
	return ob->long(this_player());
    return "";
}

/*
 * Function name: catch_msg
 * Description:   This function is called for normal messages sent to
 *                the steed.  Used for forwarding say's and the like.
 * Arguments:     str    - the message
 *                player - The object generating the message
 */
void
catch_msg(mixed str, object player)
{
    if (!player)
	player = this_player();
    ::catch_msg(str, player);
    if (player == this_object())
	return;
    if (player && environment(player) == this_object())
	tell_room(environment(), str, this_object(), player);
    else {
	force_env = 1;
	tell_room(this_object(), str, this_object(), player);
	force_env = 0;
    }
}

/*
 * Function name: long_desc
 * Description:   VBFC to give a proper long description according to
 *                where the player is (mounted or not)
 * Returns:       The long description
 */
nomask varargs string
long(mixed for_obj)
{
    object ob, *ob_list, *lv, *dd;
    string str, tmp, item, it, *ctants;
    int brief, max;

    if (!for_obj)
	for_obj = this_player();
    if (objectp(for_obj) && environment(for_obj) == this_object()) {
	brief = this_player()->query_brief();
	str = "You are astride your " + query_race_name() + ", " +
	    query_the_name(this_player()) + ". ";
	str += "From here you can see:\n";
	if (this_player()->query_wiz_level()) {
	    tmp = file_name(environment());
	    if (strlen(environment()->query_prop(OBJ_S_WIZINFO)))
		tmp = "Wizinfo " + tmp;
	    str += tmp + "\n";
	}

	if (!(environment(this_object()) &&
	      (environment(this_object())->query_prop(OBJ_I_LIGHT) >
	       -(this_player()->query_prop(LIVE_I_SEE_DARK)))))
	    str += LD_DARK_LONG;
	else {
	    ob = environment();
	    if (!ob->check_seen(this_player()))
		str += LD_CANT_SEE;
	    else {
#ifdef DAY_AND_NIGHT
		if (!ob->query_prop(ROOM_I_INSIDE) &&
		    (HOUR>21 || HOUR<5) && (ob->query_prop(ROOM_I_LIGHT) +
		     this_player()->query_prop(LIVE_I_SEE_DARK)) < 2)
		    str += LD_IS_NIGHT(ob);
		else
#endif
		if (brief) {
		    str += ob->short() + ".\n";
		    if (!ob->query_noshow_obvious())
			str += ob->exits_description();
		}
		else
		    str += ob->long();
		ob_list = all_inventory(environment());
		lv = filter(ob_list, "filter_other_living", FILTER_FILE);
		lv -= ({ this_object() });
		dd = filter(ob_list, "filter_dead", FILTER_FILE);
		dd = filter(dd, "filter_shown", FILTER_FILE);

		item = COMPOSITE_FILE->desc_dead(dd, 1);
		if (item)
		    str += break_string(capitalize(item) + ".", 76) + "\n";
		item = COMPOSITE_FILE->desc_live(lv, 1);
		if (item)
		    str += break_string(capitalize(item) + ".", 76) + "\n";
		for (max=0 ; max<sizeof(lv) ; max++) {
		    ctants = map(lv[max]->query_enemy(-1), "fights",
				 this_object(), lv[max]);
		    if (sizeof(ctants))
			ctants -= ({ 0 });
		    if (sizeof(ctants) == 1)
			item = LD_FIGHT1(ctants[0]);
		    else if (sizeof(ctants) > 1)
			item = LD_FIGHT_MANY(ctants);
		    else
			item = 0;
		    if (item)
			str += LD_FIGHT_DESC(item, lv[max]);
		}
	    }
	}
    }
    else
	return ::long(for_obj);
    return str;
}

/*
 * Function name: light_value
 * Description:   Get the light value of the steed.  Only used when
 *                mounted
 * Returns:       1 for players in the steeds inventory, 0 for others
 */
nomask int
light_value()
{
    int n;

    for (n=0 ;; n--)
	if (!calling_function(n))
	    break;
    n++;
    if (force_env || environment(calling_object(n)) == this_object())
	return environment()->query_prop(OBJ_I_LIGHT);
    return 0;
}

/*
 * Function name: set_owner
 * Description:   Set up the name of the player owning the steed
 * Arguments:     str - the name of the owner
 */
void
set_owner(string str)
{
    if (str)
	owner = str;
}

/*
 * Function name: set_long
 * Description:   Set up the general long desc of the steed
 * Arguments:     str - the long desc
 */
void
set_long(string str)
{
    if (str)
	my_long = str;
}

/*
 * Function name: set_age
 * Description:   Set up the age of the steed
 * Arguments:     i - the age in seconds
 */
void
set_age(int i)
{
    age = i;
}

/*
 * Function name: set_max_age
 * Description:   Set up the max. age of the steed
 * Arguments:     i - the max. age in seconds
 */
void
set_max_age(int i)
{
    max_age = i;
}

/*
 * Function name: query_age
 * Description:   Get the current age of the steed
 * Returns:       The current age in seconds
 */
int
query_age()
{
    return age + CHECK_TIME - find_call_out("check_age");
}

/*
 * Function name: check_age
 * Description:   Check the steeds age wrt. the max. age
 */
void
check_age()
{
    call_out("check_age", CHECK_TIME);
    age += CHECK_TIME;
    if (max_age - age <= 0) {
	remove_call_out("check_age");
	tell_room(environment(), QCTNAME(this_object()) + " starts sagging, "+
		  "as if about to fall.\n", this_object());
	tell_room(this_object(), QCTNAME(this_object()) + " starts sagging, "+
		  "as if about to fall.\n", this_object());
	heal_hp(-query_max_hp());
	this_object()->do_die(this_object());
    }
    else if (max_age - age <= max_age / 10) {
	tell_room(environment(), QCTNAME(this_object()) + " is starting "+
		  "to look old.\n", this_object());
	tell_room(this_object(), QCTNAME(this_object()) + " is starting "+
		  "to look old.\n", this_object());
    }
}

/*
 * Function name: init_living
 * Description:   Add some commands to the steed
 */
void
init_living()
{
    ::init_living();
    if (this_player()->query_real_name() != owner)
	return;
    if (environment(this_player()) == this_object())
	add_action("do_command", "", 1);
    else {
	add_action("do_mount", "mount");
	add_action("do_lead", "lead");
	add_action("do_stay", "stay");
	add_action("do_release", "release");
	add_action("do_feed", "feed");
    }
    add_action("do_vitals", "svitals");
}

/*
 * Function name: do_command
 * Description:   Do commands while mounted
 * Arguments:     arg - the command string
 * Returns:       0 - command successful
 *                1 - command not succesful
 */
nomask int
do_command(string arg)
{
    string thefunction, *exits;
    int i;

    /*
     * Check if it is an internal command
     */
    thefunction = command_map[query_verb()];
    if (!thefunction) {
	/*
	 * No, it was not.  Check if it is an exit added by a room
	 * using add_exit()
	 */
	exits = environment()->query_exit();
	for (i=0 ; i<sizeof(exits) ; i += 3)
	    if (exits[i + 1] == query_verb()) {
		thefunction = "do_dir";
		break;
	    }
	/*
	 * Still no luck, defer to other objects
	 */
	if (!thefunction)
	    return 0;
    }
    return call_other(this_object(), thefunction, arg);
}

/*
 * Function name: do_dir
 * Description:   The player asked to move in a direction, let the
 *                steed do it
 * Arguments:     arg - the rest of the command
 * Returns:       1 - command successful
 */
nomask int
do_dir(string arg)
{
    object env, ob, *ob_list, *lv, *dd, rider, cbobj;
    string tmp, item, it, *ctants, verb;
    mixed exits, enemies;
    int brief, max, i;

    env = environment();
    verb = query_verb();
    exits = env->query_prop(STEED_AS_NOT_RIDE);
    if (sizeof(exits) && member_array(verb, exits) >= 0) {
	write("You cannot ride your " + query_race_name() + " in that " +
	      "direction.\n");
	return 1;
    }
    exits = env->query_prop(STEED_AS_NO_ENTER);
    if (sizeof(exits) && member_array(verb, exits) >= 0) {
	write("Your " + query_race_name() + " cannot go there.\n");
	return 1;
    }
    if (arg)
	verb += " " + arg;
    rider = find_player(owner);
    if (rider && environment(rider) == this_object()) {
	if (rider->resolve_task(TASK_ROUTINE,
				({ TS_DEX, SS_RIDING })) < 1) {
	    exits = env->query_exit();
	    if (exits) {
		max = random(sizeof(exits) / 3);
		verb = exits[max * 3 + 1];
	    }
	}
	else if (rider->resolve_task(TASK_ROUTINE,
				     ({ TS_DEX, SS_RIDING })) < 1) {
	    rider->catch_msg("You are thrown off your " + query_race_name() +
			     "!\n");
	    say(QCTNAME(rider) + " is thrown off " + rider->query_possessive()+
		" " + query_race_name() + "!\n", ({ this_object(), rider }));
	    rider->move_living("M", environment(), 1, 1);
	    ob = query_attack();
	    if (ob) {
		stop_fight(ob);
		ob->stop_fight(this_object());
		this_player()->catch_msg("You attack " + QTNAME(ob) +
					 ".\n");
	    }
	    enemies = query_enemy(-1);
	    cbobj = this_player()->query_combat_object();
	    for (i=0 ; i<sizeof(enemies) ; i++)
		cbobj->cb_add_enemy(enemies[i], 1);
	    stop_fight(enemies);
	}
    }
    command(verb);
    if (environment() != env && environment(this_player()) == this_object()) {
	brief = this_player()->query_brief();
	if (this_player()->query_wiz_level()) {
	    tmp = file_name(environment());
	    if (strlen(environment()->query_prop(OBJ_S_WIZINFO)))
		tmp += "Wizinfo " + tmp;
	    tell_object(this_player(), tmp + "\n");
	}

	if (!(environment(this_object()) &&
	      (environment(this_object())->query_prop(OBJ_I_LIGHT) >
	       -(this_player()->query_prop(LIVE_I_SEE_DARK)))))
	    write(LD_DARK_LONG);
	else {
	    ob = environment();
	    if (!ob->check_seen(this_object()))
		write(LD_CANT_SEE);
	    else {
#ifdef DAY_AND_NIGHT
		if (!ob->query_prop(ROOM_I_INSIDE) &&
		    (HOUR>21 || HOUR<5) && (ob->query_prop(ROOM_I_LIGHT) +
		     this_player()->query_prop(LIVE_I_SEE_DARK)) < 2)
		    write(LD_IS_NIGHT(ob));
		else
#endif
		if (brief) {
		    write(ob->short() + ".\n");
		    if (!ob->query_noshow_obvious())
			write(ob->exits_description());
		}
		else
		    write(ob->long());
		ob_list = all_inventory(environment());
		lv = filter(ob_list, "filter_other_living", FILTER_FILE);
		lv -= ({ this_object() });
		dd = filter(ob_list, "filter_dead", FILTER_FILE);
		dd = filter(dd, "filter_shown", FILTER_FILE);

		item = COMPOSITE_FILE->desc_dead(dd, 1);
		if (item)
		    write(break_string(capitalize(item) + ".", 76) + "\n");
		item = COMPOSITE_FILE->desc_live(lv, 1);
		if (item)
		    write(break_string(capitalize(item) + ".", 76) + "\n");
		for (max=0 ; max<sizeof(lv) ; max++) {
		    ctants = map(lv[max]->query_enemy(-1), "fights",
				 this_object(), lv[max]);
		    if (sizeof(ctants))
			ctants -= ({ 0 });
		    if (sizeof(ctants) == 1)
			item = LD_FIGHT1(ctants[0]);
		    else if (sizeof(ctants) > 1)
			item = LD_FIGHT_MANY(ctants);
		    else
			item = 0;
		    if (item)
			write(LD_FIGHT_DESC(item, lv[max]));
		}
	    }
	}
    }
    else
	write("The " + query_race_name() + " cannot do that.\n");
    return 1;
}

/*
 * Function name: mtrig_follow
 * Description:   Called by the movement code when the player we are
 *                following has left
 * Arguments:     s1, s2 - the strings surrounding the name of the
 *                         player leaving
 * Returns:       1 - trigger processed
 *                0 - trigger not processed
 */
nomask int
mtrig_follow(string s1, string s2)
{
    object env;
    string *words;
    mixed *ex;
    int il;

    if (!(env = environment(this_object())))
	return 0;

    if (lower_case(s1) != owner)
	return 0;

    s2 = implode(explode(s2 + "\n", "\n"), " ");

    words = explode(s2 + " "," ");

    if ((member_array("says:", words) < 0) &&
	(member_array("shouts:", words) < 0))
    {
	ex = (mixed*)environment(this_object())->query_exit();

	for (il = 1; il < sizeof(ex); il += 3)
	{
	    if ((member_array(ex[il], words) >= 0) ||
		(member_array(ex[il] + ".", words) >= 0))
	    {
		words = env->query_prop(STEED_AS_NO_ENTER);
		if (!sizeof(words) || member_array(ex[il], words) < 0)
		    call_out("command", 2, ex[il]);
		return 1;
	    }
	}
    }
    return 0;
}

/*
 * Function name: show_age
 * Description:   Make a readable string of the number returned by the
 *                function query_age(). 
 * Returns:       The age string, e.g.: "1 day 5 minutes 37 seconds".
 */
public string
show_age()
{
    int i, j;
    string str;

    str = "";
    i = query_age();
    if (j = i / 43200)
    {
        if (j > 1)
            str += " " + j + " days";
        else
            str += " 1 day";
        i = i - j * 43200;
    }
    if (j = i / 1800)
    {
        if (j > 1)
            str += " " + j + " hours";
        else
            str += " 1 hour";
        i = i  - j * 1800;
    }
    if (j = i / 30)
    {
        if (j > 1)
            str += " " + j + " minutes";
        else
            str += " 1 minute";
        i = i - (i / 30) * 30;
    }
    if ((j = i * 2) > 1)
        str += " " + i * 2 + " seconds";
    else if (j == 1)
        str += " 1 second";

    return str;
}

/*
 * Function name: do_vitals
 * Description:   Allow the owner to check the steed's vitals
 * Arguments:     arg - the rest of the command
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_vitals(string arg)
{
    int a, b, i, j;
    string s, s2, s3, s4, t;

    notify_fail("Vitals on what?\n");
    if (arg)
	return 0;
    notify_fail("This is not your " + query_race_name() + ".\n");
    if (this_player()->query_real_name() != owner)
	return 0;

    s = capitalize(query_pronoun());
    s2 = s + " has ";
    s3 = s + " feels "; 
    s4 = s + " can ";
    s = s + " is ";

    /* height, width, race
     */

    /* Hitpoints and mana
     */
    a = (query_hp() * 100) / query_max_hp();
    t = "/cmd/live/state"->get_proc_text(a, SD_HEALTH, 0, ({}));
    b = (query_mana() * 100) / query_max_mana();

    write(s + "physically " + t + " and mentally " +
          "/cmd/live/state"->get_proc_text(b, SD_MANA, 0, ({})) + ".\n");

    /* panic
     */
    a = (10 + query_stat(SS_DIS) * 3);
    b = query_panic();
    a = 100 * b / (a != 0 ? a : b);
    t = "/cmd/live/state"->get_proc_text(a, SD_PANIC, 2) + " and ";

    /* fatigue
     */
    a = query_max_fatigue();
    b = a - query_fatigue();
    a = 100 * b / (a != 0 ? a : b);
    t += "/cmd/live/state"->get_proc_text(a, SD_FATIGUE, 1) + ".";

    write(break_string(s3 + t, 76) + "\n");
    
    /* stuffed
     */
    a = query_prop(LIVE_I_MAX_EAT);
    b = query_stuffed();
    a = 100 * b / (a != 0 ? a : b);
    t = "/cmd/live/state"->get_proc_text(a, SD_STUFF, 0, ({})) + " and ";

    /* soaked
     */
    a = query_prop(LIVE_I_MAX_DRINK);
    b = query_soaked();
    a = 100 * b / (a != 0 ? a : b);
    t += "/cmd/live/state"->get_proc_text(a, SD_SOAK, 0, ({})) + ".";

    write(break_string(s4 + t, 76) + "\n");

    /* intox
     */
    a = query_prop(LIVE_I_MAX_INTOX);
    b = query_intoxicated();
    a = 100 * b / (a != 0 ? a : b);
    if (b)
        write(s + "/cmd/live/state"->get_proc_text(a, SD_INTOX, 0) + ".\n");
    else
    {
        /* headache
         */
        a = query_prop(LIVE_I_MAX_INTOX);
        b = query_headache();
        a = 100 * b / (a != 0 ? a : b);
        if (b)
            write(s + "sober, but " + s2 + 
                  LANG_ADDART("/cmd/live/state"->get_proc_text(a, SD_HEADACHE, 1)) +
                  " headache.\n");
        else
            write(s + "sober.\n");
    }

    /* weight, volume (This tells us what we can carry)
     */

    /*
     * Alignment
     */
    t = query_align_text();

    write(s + t + ".\n");

    /*
     * Carry
     */
    a = query_encumberance_weight();
    if (a >= 20)
    {
        a -= 20;
        write(s + "/cmd/live/state"->get_proc_text(a * 100 / 75, SD_ENC_WEIGHT, 0, ({}) ) + ".\n");
    }

    /*
     * Age
     */
    write("Age:" + show_age() + ".\n");

    return 1;
}

/*
 * Function name: do_lead
 * Description:   The player tries to lead the steed somewhere
 * Arguments:     arg - the rest of the command
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_lead(string arg)
{
    notify_fail("Lead whom?\n");
    if (!arg || !id(arg))
	return 0;
    notify_fail("This is not your " + query_race_name() + ".\n");
    if (this_player()->query_real_name() != owner)
	return 0;
    trig_new("%w %s", "mtrig_follow");
    trig_setobjects( ({ this_player() }) );
    write("Ok.\n");
    return 1;
}

/*
 * Function name: do_stay
 * Description:   The player stops leading the steed
 * Arguments:     arg - the rest of the command
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_stay(string arg)
{
    notify_fail("Tell whom to stay?\n");
    if (!arg || !id(arg))
	return 0;
    notify_fail("This is not your " + query_race_name() + ".\n");
    if (this_player()->query_real_name() != owner)
	return 0;
    trig_delete("%w %s");
    write("Ok.\n");
    return 1;
}

/*
 * Function name: do_release
 * Description:   The player releases the steed to the stables
 * Arguments:     arg - the rest of the command
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_release(string arg)
{
    notify_fail("Release whom?\n");
    if (!arg || !id(arg))
	return 0;
    notify_fail("This is not your " + query_race_name() + ".\n");
    if (this_player()->query_real_name() != owner)
	return 0;
    call_out("remove_steed", 5, 0);
    write("Ok.\n");
    return 1;
}

/*
 * Function name: do_feed
 * Description:   The player tries to feed the steed
 * Arguments:     arg - the rest of the command
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_feed(string arg)
{
    string who, what;
    object ob;

    notify_fail("Feed whom?\n");
    if (!arg)
	return 0;
    notify_fail("This is not your " + query_race_name() + ".\n");
    if (this_player()->query_real_name() != owner)
	return 0;
    notify_fail("Feed whom with what?\n");
    if (sscanf(arg, "%s with %s", who, what) != 2 &&
	sscanf(arg, "%s to %s", what, who) != 2)
	return 0;
    if (!id(who))
	return 0;
    notify_fail("You don't carry that!\n");
    if (!(ob = present(what, this_player())))
	return 0;
    notify_fail("That does not qualify as food!\n");
    if (!ob->eat_access(ob))
	return 0;
    notify_fail("Your " + query_race_name() + " refuses to eat that.\n");
    if (!this_object()->query_is_food(ob))
	return 0;
    if (eat_food(ob->query_amount(), 0)) {
	command("emote eats some food.");
	ob->split_heap(1);
	ob->destruct_object();
    }
    else
	write("Your " + query_race_name() + " is unable to eat that.\n");
    return 1;
}

/*
 * Function name:   remove_steed
 * Description:     Return a steed to the stables
 */
nomask void
remove_steed(int force)
{
    object ob, *obs;
    int i;

    if (!force && sizeof(FILTER_LIVE(all_inventory())))
	return;
    tell_room(environment(), QCTNAME(this_object()) + " returns to "+
	      query_possessive() + " stable.\n", this_object());
    ob = find_player(owner);
    if (ob) {
	obs = FIND_STR_IN_OBJECT("_steed_controller_", ob);
	for (i=0 ; i<sizeof(obs) ; i++)
	    if (id(obs[i]->query_horse_name())) {
		obs[i]->update_values();
		break;
	    }
    }
    remove_object();
}

/*
 * Function name:   fights
 * Description:     Find out who fights who.
 * Arguments:       me, enemy: The fighting folks
 * Returns:         "you" if the enemy is fighting me, or else his name
 */
static nomask mixed
fights(object me, object enemy)
{
    if (!objectp(me))
	return 0;
    if (me->query_enemy(0) == enemy) {
	if (me == this_object())
	    return "you and your " + query_race_name();
	else
	    return me->query_the_name(this_player());
    }
    else
	return 0;
}

/*
 * Function name: do_mount
 * Description:   Mount the steed
 * Arguments:     arg - the rest of the command string
 * Returns:       1 - command succesful
 *                0 - command not succesful
 */
nomask int
do_mount(string arg)
{
    object *enemies;
    int i;

    notify_fail("Mount what?\n");
    if (!arg || !id(arg))
	return 0;
    /*
     * Only allow the steeds owner to mount it
     */
    notify_fail("This is not your " + query_race_name() + ".\n");
    if (this_player()->query_real_name() != owner)
	return 0;
    if (this_player()->query_attack())
	write("You are too busy fighting to do that.\n");
    else if (environment(this_player())->query_prop(ROOM_I_INSIDE))
	write("There is not enough room for you to do that here.\n");
    else if (this_player()->resolve_task(TASK_ROUTINE,
					 ({ TS_DEX, SS_RIDING })) > 0) {
	add_prop(ROOM_I_IS, 1);
	this_player()->remove_prop(OBJ_M_NO_GET);
	tell_room(environment(), QCTNAME(this_player()) + " mounts "+
		  this_player()->query_possessive() + " " + query_race_name() +
		  ".\n", ({ this_object(), this_player() }));
	if (this_player()->move_living("M", this_object(), 1, 1))
	    write("Your " + query_race_name() + " is unable to carry you.\n");
	else {
	    write("You mount your " + query_race_name() + ".\n");
	    trig_delete("%w %s");
	    enemies = this_player()->query_enemy(-1);
	    CEX;
	    for (i=0 ; i<sizeof(enemies) ; i++)
		combat_extern->cb_add_enemy(enemies[i], 1);
	    this_player()->stop_fight(enemies);
	}
	this_player()->add_prop(OBJ_M_NO_GET, 1);
	remove_prop(ROOM_I_IS);
    }
    else {
	write("The " + query_race_name() + " will not let you mount.\n");
	say(QCTNAME(this_player()) + " tries to mount " +
	    this_player()->query_possessive() + " " + query_race_name() +
	    ", but the " + query_race_name() + " refuses to cooperate.\n");
    }
    return 1;
}

/*
 * Function name: do_dismount
 * Description:   Dismount the steed
 * Arguments:     arg - the rest of the command string
 * Returns:       1 - command succesful
 *                0 - command not succesful
 */
nomask int
do_dismount(string arg)
{
    object cbobj, enemy;
    mixed enemies;
    int i;

    notify_fail("Dismount what?\n");
    if (arg && !id(arg))
	return 0;
    tell_room(environment(), QCTNAME(this_player()) + " dismounts "+
	      this_player()->query_possessive() + " " + query_race_name() +
	      ".\n", ({ this_object(), this_player() }));
    write("You dismount your " + query_race_name() + ".\n");
    this_player()->move_living("M", environment(), 1, 1);
    enemy = query_attack();
    if (enemy) {
	stop_fight(enemy);
	enemy->stop_fight(this_object());
	this_player()->catch_msg("You attack " + QTNAME(enemy) + ".\n");
    }
    enemies = query_enemy(-1);
    cbobj = this_player()->query_combat_object();
    for (i=0 ; i<sizeof(enemies) ; i++)
	cbobj->cb_add_enemy(enemies[i], 1);
    stop_fight(enemies);
    return 1;
}

nomask void
look_living_exec(mixed plr)
{
    write(plr->long(this_object()));
}

/*
 * Function name: show_exec
 * Description:   Shows an item depending on its position, normally the long
		  description, but short description for items carried or
		  inside other items.
 * Arguments:	  object ob
 *
*/
nomask void 
show_exec(object ob)
{
    object env;
    string str;
    
    env = environment(ob); str = 0;

    if (env == this_player() || env == environment())
	write(ob->long(this_object()));
    
    /* objects inside transparent objects */
    while (env != this_player() && env != environment(this_object()))
    {
	if (!str)
	    str = "You see " + LANG_ASHORT(ob);
	if (living(env))
	    str += " carried by " + env->short(this_object());
	else
	    str += " inside the " + env->short();
	env = environment(env);
    }

    if (str) {
	str += ".\n";
	write(break_string(str, 76));
    }
}

/*
 * Function name: item_access
 * Description:   test if an object contains (pseudo) item description gItem
 * Arguments:	  object ob
 * Returns:       1: found gItem
                  0: failed to find gItem
 * Globals:       string gItem
 *
*/
nomask int 
item_access(object ob)
{
    if (!objectp(ob))
	return 0;
    return (int) ob->item_id(gItem);
}

/* 
 * Is 
 */
nomask int
visibly_hold(object ob)
{
    object env;
    if (!objectp(ob))
	return 0;
 
    env = environment(ob);
    while (objectp(env))
    {
	if (env->query_prop(CONT_I_HIDDEN) ||
	    (!env->query_prop(CONT_I_TRANSP) &&
	     !env->query_prop(CONT_I_ATTACH) &&
	     env->query_prop(CONT_I_CLOSED)))
	    return 0;
	else
	    env = environment(env);
    }
    return 0;
}

nomask int
inside_visible(object cobj)
{
    object env;

    if (!objectp(cobj) || cobj->query_no_show())
	return 0;

    /* Properties stop us from seing the inside
     */
    if (!cobj->query_prop(CONT_I_IN) || cobj->query_prop(CONT_I_HIDDEN) ||
		(cobj->query_prop(CONT_I_CLOSED) &&
	 	!cobj->query_prop(CONT_I_TRANSP) &&
	 	!cobj->query_prop(CONT_I_ATTACH)))
	return 0;        

    env = environment(cobj);
    if (env == this_object() || env == environment(this_object()) ||
		visibly_hold(cobj))
	return 1;

    while (env && (!env->query_prop(CONT_I_CLOSED) ||
	    env->query_prop(CONT_I_TRANSP)) && !env->query_no_show())
    {
        if (visibly_hold(env))
	    return 1;
	env = environment(env);
	if (env == this_object() || env == environment(this_object()))
	    return 1;
    }
    return 0;
}

varargs nomask int
visible(object ob, object cobj)
{
    object env;

    if (!objectp(ob))
	return 0;

    if (cobj && (env = (object)cobj->query_room()) &&
		(cobj->query_prop(CONT_I_TRANSP) ||
		!cobj->query_prop(CONT_I_CLOSED)))
	return ((env->query_prop(OBJ_I_LIGHT) >
		-(this_object()->query_prop(LIVE_I_SEE_DARK))) && 
		CAN_SEE(this_object(), ob));
	
    env = environment(ob);
    if (env == this_object() || env == environment(this_object()))
	return CAN_SEE(this_object(), ob);

    while (objectp(env) && !living(env) && (env->query_prop(CONT_I_TRANSP) ||
		!env->query_prop(CONT_I_CLOSED)))
    {
	env = environment(env);
	if (env == this_object() || env == environment(this_object()))
	    return CAN_SEE(this_object(), ob);
    }
    return 0;
}

/*
 * Function name: do_look
 * Description:   Executed when the player wants to look at or examine
 *                something
 * Arguments:     arg - the trailing command string
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_look(string arg)
{
    string          prp,
                    prplc,
		    *tmp,
                    name;
    int             i;
    object          *obarr,
                    *obd,
                    *obl,
		    ob;

    if (!arg)
	return 0;

    if (query_verb() == "exa" || query_verb() == "examine")
	arg = "prp_examine " + arg;
    
    arg = lower_case(arg);
    tmp = explode(arg, " ");
    if (sizeof(tmp) > 1 && tmp[1][0] == '0')
	return 0;
	
    /* test for preposition */
    if (sscanf(arg, "%s %s", prp, name) < 2)
	return 0;

    prplc = lower_case(prp);
    if (prplc != "at" && prplc != "in" && prplc != "inside" &&
	prplc != "prp_examine")
	return 0;
    /* through, under, behind, .. ? */

    gItem = lower_case(name);

    if ((prplc == "prp_examine" || prplc == "at") && id(gItem) &&
	CAN_SEE_IN_ROOM(this_object())) {
	write("You are astride your " + query_race_name() + ".\n" + my_long + "\n");
	return 1;
    }

    if (!parse_command(arg, environment(this_object()), "%w %i", prp, obarr) ||
	!sizeof(obarr = VISIBLE_ACCESS(obarr, "visible", this_object())))
    {
	/* No objects found */
	/* Test for pseudo item in the environment */
	if (environment(this_object())->item_id(gItem) &&
		CAN_SEE(this_object(), environment(this_object())))
	{
	    write(environment(this_object())->long(gItem));
	    return 1;
	}
	else
	{
	    obarr = deep_inventory(environment(this_object()));
	    obarr = filter(obarr, "visible", this_object());
	    obarr = filter(obarr, "item_access", this_object()); 
	    if (sizeof(obarr) > 0) {
		for (i = 0; i < sizeof(obarr); i++)
		    write(obarr[i]->long(gItem));
		return 1;
	    } else {
		if (name == "enemy" && (this_player()->query_attack() ||
					this_object()->query_attack()))
		{
		    ob = this_player()->query_attack();
		    if (!ob)
			ob = this_object()->query_attack();
		    write(ob->long(this_object()));
		    return 1;
		}
		return 0;
	    }
	}
    }

    if (sizeof(obarr) == 0)
	return 0;

    if (prplc == "at" || prplc == "prp_examine")
    {
	obd = FILTER_DEAD(obarr);
	obl = FILTER_LIVE(obarr);
	if (sizeof(obd) == 0 && sizeof(obl) == 0)
	    return 0;

	/* if single container we show the contents */
	if (sizeof(obd) == 1 && inside_visible(obd[0]))
	{
	    show_exec(obd[0]);
	} else
	    map(obd, "show_exec", this_object());

	/* if a single living being we show carried items */
	if (sizeof(obl) == 1)
	    look_living_exec(obl[0]);
	else
	    map(obl, "show_exec", this_object());

        /* if we are looking at many dead objects perhaps such an object 
	 * exists in the room too? If gItem has another singular form then
	 * we suspect player gave a plural word to look for. Should work
	 * in most cases. */
	if (LANG_SWORD(gItem) != gItem &&
		environment(this_object())->item_id(gItem))
	    write(environment(this_object())->long(gItem));

	return 1;
    }
    return 0;
}

/*
 * Function name: do_die
 * Description:   Called when the steed dies
 * Arguments:     killer - object that killed the steed
 */
nomask void
do_die(object killer)
{
    object ob, *obs;
    int i;

    seteuid(getuid());
    if (!killer)
	killer = previous_object();
    REGISTRY->steed_died(owner);
    obs = all_inventory();
    for (i=0 ; i<sizeof(obs) ; i++) {
	if (living(obs[i])) {
	    obs[i]->catch_msg("As " + QTNAME(this_object()) + " dies, "+
			      "you are thrown off.\n");
	    tell_room(environment(), QCTNAME(obs[i]) + " falls off "+
		      QTNAME(this_object()) + ".\n");
	    obs[i]->move_living("M", environment(), 1, 1);
	}
	else
	    obs[i]->move(environment());
    }
    ob = find_player(owner);
    if (ob) {
	obs = FIND_STR_IN_OBJECT("_steed_controller_", ob);
	if (sizeof(obs))
	    obs->remove_object();
    }
    ::do_die(killer);
}

/*
 * Function name: enter_inv
 * Description:   Add item descript to players mounting the steed
 * Arguments:     ob   - entering object
 *                from - the previous location of the object
 */
nomask void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob) && ob->query_real_name() == owner) {
	add_item(ob->query_real_name(),
		 "@@rider_desc|" + ob->query_real_name() + "@@");
	ob->add_subloc(RIDING_SUBLOC, this_object());
    }
    else if (!ob->query_prop(STEED_I_BACKPACK))
	if (ob->move(environment()))
	    ob->move(environment(), 1);
}

/*
 * Function name: leave_inv
 * Description:   Remove item descript to players dismounting the steed
 * Arguments:     ob - entering object
 *                to - the new location of the object
 */
nomask void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    if (living(ob)) {
	remove_item(ob->query_real_name());
	ob->remove_subloc(RIDING_SUBLOC);
    }
}

/*
 * Function name: show_subloc
 * Description:   Display a subloc description for a mounted player
 * Arguments:     subloc - the name of the subloc to be described
 *                on     - the object being described
 *                for_ob - the object wanting the description
 * Returns:       The description
 */
nomask string
show_subloc(string subloc, object on, object for_ob)
{
    string str;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
	subloc != RIDING_SUBLOC)
	return "";
    if (for_ob == on)
	return "You are mounted on your " + query_race_name() + ".\n";
    return capitalize(on->query_pronoun()) + " is mounted on " +
	   on->query_possessive() + " " + query_race_name() + ".\n";
}

/*
 * Function name: start_remove
 * Description:   Called from the pedigree when the player logs out to
 *                remove the steed from the game
 */
nomask void
start_remove()
{
    call_out("remove_steed", 2, 1);
}

void
savevars_delay_reset()
{
    last_stuffed = query_stuffed();
    ::savevars_delay_reset();
}

void
calculate_fatigue()
{
    int n, stuffed, tmpstuffed;

    n = (time() - fatigue_time) / F_INTERVAL_BETWEEN_FATIGUE_HEALING;
    if (n > 0)
    {
        stuffed = query_stuffed();
        tmpstuffed = (stuffed + last_stuffed) / 2;
        add_fatigue(n * 5 *
            F_FATIGUE_FORMULA(tmpstuffed, query_prop(LIVE_I_MAX_EAT)));
        last_stuffed = stuffed;
        fatigue_time += n * F_INTERVAL_BETWEEN_FATIGUE_HEALING;
    } 

}

/*
 * Function name:   query_stuffed
 * Description:     Gives the level of stuffedness of a living.
 * Returns:         The level of stuffedness.
 */
public int
query_stuffed()
{
    int t, n;

    n = (time() - stuffed_time) / F_INTERVAL_BETWEEN_STUFFED_HEALING;

    if (n == 0)
        return stuffed;

    stuffed -= F_UNSTUFF_RATE * n * 2;
    stuffed = MAX(0, stuffed);

    stuffed_time += n * F_INTERVAL_BETWEEN_STUFFED_HEALING;
    
    return stuffed;
}

/*
 * Function name:   set_stuffed
 * Description:     Set the level of stuffedness of a living
 * Arguments:       i: The level of stuffedness
 */
static void
set_stuffed(int i)
{
    calculate_fatigue();
    stuffed = i;
}

/*
 * Function name: do_join
 * Description:   Executed when the player wants to join a team
 * Arguments:     arg - the trailing command string
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_join(string name)
{
    object          leader;

    notify_fail("You must give the name of the player you want as " +
	"your leader.\n");

    if (!name)
	return 0;

    if (this_object()->query_leader())
    {
	write("You already have a leader!\n");
	return 1;
    }

    if (!this_player()->query_met(name))
    {
	write("You don't know anyone called '" + capitalize(name) + "'.\n");
	return 1;
    }

    leader = present(name, environment());

    if (!leader || !leader->check_seen(this_object()))
    {
	write("You don't see " + capitalize(name) + " here.\n");
	return 1;
    }

    /*
     * Can not have a leader with too low DIS
     */
    if (leader->query_stat(SS_DIS) + 10 < this_player()->query_stat(SS_DIS) &&
		!this_player()->query_wiz_level())
    {
	write("You do not have enough faith in " + 
	      LANG_POSS(leader->short()) + " discipline.\n");
	return 1;
    }

    if (leader->team_join(this_object()))
    {
	write("Your leader is now: " + leader->short() + ".\n");
	say(QCTNAME(this_player()) + " joined the team of " +
		QTNAME(leader) + ".\n", ({ leader, this_player() }));
	leader->catch_msg(this_player()->query_The_name(leader) +
	    " joined your team.\n");
	return 1;
    }
    else
    {
	write(leader->short() +
	      " has not invited you as a team member.\n");
	return 1;
    }
}

/*
 * Function name: do_leave
 * Description:   Executed when the player wants to leave a team or
 *                remove someone as member of the team
 * Arguments:     arg - the trailing command string
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_leave(string name)
{
    object ob;

    /* This function used to have 'reveal_me' calls in players, though
     * that is nonsense since you do not even have to be in the same room
     * to leave a team or force a member to leave your team. /Mercade
     */

    if (!strlen(name))
    {
	if (objectp(ob = query_leader()))
	{
	    ob->team_leave(this_object());
	    write("You leave your leader.\n");
	    ob->catch_msg(this_player()->query_The_name(ob) +
		" left your team.\n");

	    return 1;
	}

	if (sizeof(query_team()))
	{
	    notify_fail("You are leading a team. To force a member to " +
		"leave, do <leave name>.\n");
	    return 0;
	}

	notify_fail("You are not a member of a team.\n");
	return 0;
    }

    if (!sizeof(query_team()))
    {
	notify_fail("You are not the leader of a team. Do <leave> to " +
	    "leave your leader.\n");
	return 0;
    }

    if (!objectp(ob = find_player(name)))
    {
	notify_fail("No such player, \"" + capitalize(name) + "\".\n");
	return 0;
    }

    if ((ob->query_leader()) != this_object())
    {
	notify_fail("No member named \"" + capitalize(name) +
	    "\" in your team.\n");
	return 0;
    }

    team_leave(ob);
    this_object()->remove_invited(ob); /* disallow him/her to rejoin. */
    write("You force " + ob->query_the_name(this_player()) +
	" to leave your team.\n");
    ob->catch_msg(this_player()->query_The_name(ob) + " forces you to leave " +
	this_player()->query_possessive() + " team.\n");

    return 1;
}

/*
 * Function name: do_invite
 * Description:   Executed when the player wants to invite a player to
 *                join the team
 * Arguments:     arg - the trailing command string
 * Returns:       1 - command successful
 *                0 - command not successful
 */
nomask int
do_invite(string name)
{
    object *member_list, member;

    if (!name)
    {
	member_list = this_object()->query_invited();
	if (!member_list || !sizeof(member_list))
	    write("You have not invited anyone to join you.\n");
	else
	{
	    if (sizeof(member_list) == 1)
		write("You have invited " + member_list[0]->short() +
			".\n");
	    else {
		name = (string) COMPOSITE_FILE->desc_live(member_list);
		write("You have invited " +
		      (string) LANG_FILE->word_num(sizeof(member_list)) +
		      " people:\n");
		write(break_string(name, 76, 3));
	    }
	}
	return 1;
    }

    member = find_player(name);

    if (!member || (member && !present(member, environment())))
    {
	notify_fail(capitalize(name) +
		    " is not a good potential team member!\n");
	return 0;
    }

    if (!CAN_SEE(this_object(), member))
    {
        notify_fail("Invite whom?");
        return 0;
    }

    if (query_leader())
    {
	notify_fail("You can't be a leader when you have a leader!\n");
	return 0;
    }

    if ((!member->query_met(this_player())) ||
	    (!query_met(member)))
	return (notify_fail("You have not been introduced!\n"),0);

    if (member == this_player() || member == this_object())
    {
	notify_fail("You do not need an invitation to your own team!\n");
	return 0;
    }

    this_object()->team_invite(member);
    member->catch_msg(query_The_name(member) +
	" invites you to join " + query_possessive() +
	" team.\n");
    reveal_me(1);
    member->reveal_me(1);
		
    write("Ok.\n");
    return 1;
}
