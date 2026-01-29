/*
 * File:     special_attack.h
 * Created:  Code written by Shiva
 *           Comments, special attack messages, and misc.
 *           additions by Cirion.
 *           1998.05.02
 * Purpose:  This module holds all the code for the two
 *           monk special attacks: plexus and strike.
 *           It is included in the monk shadow, so all of
 *           these functions can be called in the player, and
 *           there is no worry about too many alarms, etc.
 * Note:     This is an included file rather than an inherited
 *           one (as it should be) because many of the functions
 *           rely on inheritance of either /std/guild/guild_lay_sh
 *           or /std/guild/guild_occ_sh.
 * Modification Log:
 *
 */
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <options.h>

#include "/std/combat/combat.h"

#define TELLSW(what)         shadow_who->catch_tell(what + "\n")
#define MSGSW(what)          shadow_who->catch_msg(what + "\n")

/*
 * These macros assume the variables 'target' will be
 * meaningful. Use them only in a suitable context, when
 * all the assumed variables are set.
 */
#define TELLTARG(what)       target->catch_tell(what + "\n")
#define MSGTARG(what)        target->catch_msg(what + "\n")
#define TELLWATCHER(what)    shadow_who->tell_watcher(what + "\n", target)

#define TNAME                QTNAME(target)
#define SWNAME               QTNAME(shadow_who)
#define TCNAME               QCTNAME(target)
#define SWCNAME              QCTNAME(shadow_who)
#define THIM                 target->query_objective()
#define SWHIM                shadow_who->query_objective()
#define THIS                 target->query_possessive()
#define SWHIS                shadow_who->query_possessive()
#define THE                  target->query_pronoun()
#define SWHE                 shadow_who->query_pronoun()

/* definitions used in attack descriptions. */
#define MST_HIGH_TO_LOW        1
#define MST_HIGH_TO_HIGH       2
#define MST_LOW_TO_LOW         3
#define MST_LOW_TO_HIGH        4
#define MST_NONE               -1

#define MDESC_FOOT_RIGHT       "right foot"
#define MDESC_FOOT_LEFT        "left foot"
#define MDESC_FIST_RIGHT       "right fist"
#define MDESC_FIST_LEFT        "left fist"



static private int attack_alarm = 0;
static private int focus_level = 0;
static private int last_focus = 0;
static private int next_attack_time = 0;

public int m_query_focus();
int query_monk_special_active();

/*
 * Function name: m_may_special_attack
 * Description:   See if we are allowed to attack someone
 * Arguments:     object target - the thing we want to attack
 *                string attack - a name for the attack we want to use
 * Returns:       A string describing why we cannot attack or 0 if
 *                we can attack
 */
mixed
m_may_special_attack(object target, string attack)
{
    mixed   why;
    object  who = query_shadow_who();

    if (!target || !living(target) || !present(target, environment(shadow_who)))
        return attack + " whom?\n";
 
    if (shadow_who->query_prop(LIVE_I_ATTACK_DELAY) ||
        shadow_who->query_prop(LIVE_I_STUNNED))
        return "You are too stunned to " + attack + ".\n";
 
    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
        stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
        return why;
    else if (why)
        return "You sense a force protecting " + 
            target->query_the_name(shadow_who) + ".\n";

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(shadow_who, -1))
    {
        /* A message should be given by query_not_attack_me(), so
         * no need to specify one here.
         */
        return "";
    }

    /* Make sure we dare to attack. */
    if (!F_DARE_ATTACK(shadow_who, target))
        return "You don't dare attack.\n";

    if ((target->query_average_stat()) > (2 * (shadow_who->query_stat(SS_DIS) + 
        shadow_who->query_stat(SS_WIS) / 10)))
        return ("You don't dare try to " + attack + " " +
            target->query_the_name(shadow_who) + ".\n");

    /* Check for the _live_m_no_ block in the target. */
    if (stringp(why = target->query_prop("_live_m_no_" + attack)))
        return why;

    /* Non-humanoids cannot be hit by plexus, since they do not have one. */
    if ((attack == "plexus") && !(target->query_humanoid()))
        return target->query_The_name(shadow_who) + " does not have "
            + "a solar plexus you can hit.\n";

    if ((!shadow_who->query_npc()) && (shadow_who->query_met(target)) &&
        !(shadow_who == target->query_attack()) &&
        (shadow_who->query_prop(LIVE_O_LAST_KILL) != target))
        {
        shadow_who->add_prop(LIVE_O_LAST_KILL, target);
        return "Attack " + target->query_the_name(shadow_who) + 
            "?!? Please confirm by trying again.\n";
         }

    return 0;
}

/*
 * Function name: add_monk_attack_fatigue
 * Description:   add fatigue to the player when they perform
 *                a special attack.
 * Arguments:     none
 * Returns:       void
 */
void
add_monk_attack_fatigue()
{
    if (shadow_who->query_fatigue() < 5)
    {
        shadow_who->heal_hp(-(5 - shadow_who->query_fatigue()));
        shadow_who->set_fatigue(0);
        shadow_who->catch_tell("The strain of the attack drains you.\n");
    }
    else
    {
        // Cirion, 1999.08.22: Lowered the fatigue penalty
        //shadow_who->add_fatigue(-5);
        shadow_who->add_fatigue(-(random (3)));
    }
}

/*
 * Function name:   adjust_combat_on_move
 * Description:     Called to let movement affect the ongoing fight. This
 *                  is used to invalidate a special attack if we move.
 * Arguments:       True if leaving else arriving
 */
public void
adjust_combat_on_move(int leave)
{
    if (query_monk_special_active())
    {
        remove_alarm (attack_alarm);
        attack_alarm = 0;
        shadow_who->catch_tell("You stop preparing your attack.\n");
    }

    shadow_who->adjust_combat_on_move (leave);
}

/*
 * Function name: add_array
 * Description:   support function to add all the
 *                elements of an integer array together
 * Arguments:     the array of integers
 * Returns:       the sum of the array
 */
int
add_array(int *nums)
{
    int     i,
            tot;

    for(i=0; i<sizeof(nums); i++)
        tot += nums[i];

    return tot;
}

/*
 * Function name: query_attack_mod
 * Description:   check the attack modifier of the special
 *                attack. Checks for heavy armours,
 *                whether we are wielding a weapon.
 * Arguments:     none
 * Returns:       the attack modified. 100 implies that the
 *                attack will not be modified. 50 implies
 *                that the attack is 50% effectual.
 */
int
query_attack_mod()
{
    object  *weapons;
    int      mod,
             pfatigue,
             armweight,
             parmenc;

    /* default is 100% effectiveness */
    mod = 100;

    // cirion: 2000.01.10 penalties for fatigure and weight disabled
    // for now
    if (0)
    {
	weapons = shadow_who->query_weapon(-1);

	/* If the player is wielding two weapons, or one    */
	/* two-handed weapon, reduce the effectiveness.     */
	if ((sizeof(weapons) > 1) ||
	    ((sizeof (weapons) == 1) && (weapons[0]->query_hands() == W_BOTH)))
	    mod = 60;
	else if (sizeof(weapons))
	    /* No change if one hand is occupied */
	    return mod = 100;
	else
	    /* Bonus for no hands occupied */
	    mod = 120;

	/*
	* Adjust the effectiveness based on how tired the attack is.
	* Total fatigue will make the attack completely ineffective.
	*/
	pfatigue = (shadow_who->query_fatigue() * 100) / shadow_who->query_max_fatigue();
	mod *= pfatigue;
	mod /= 100;

	/*
	* We could detract for hunger as well, but I think that
	* is a bit much, since if the player is hungry, they
	* will become more fatigued faster.
	*
	* As for drunkness, I think I won't touch that.   -Cir.
	*/


	/*
	* Now subtract for heavy armours. The way we will do this
	* is find the total amount of weight of all armours
	* worn by the player, and then see what percentage of
	* their max encumberance the armour takes up. Multiply
	* that percentage into the modifier.    -Cir.
	*/
	armweight = add_array(shadow_who->query_armour(-1)->query_prop(OBJ_I_WEIGHT));
	parmenc = 100 - ((armweight * 100) / shadow_who->query_prop(CONT_I_MAX_WEIGHT));
    
	if (armweight > 0)
	{
	    mod *= parmenc;
	    mod /= 100;
	}
    }

    if(m_query_focus())
        mod += F_MONK_FOCUS_COMBAT_BONUS(shadow_who->query_skill(MONK_SKILL_FOCUS));

#ifdef DEBUG_COMBAT
    m_tell_guild_masters ("attacking with monk mod: " + mod + "\n", 10);
#endif

    return mod;
}

public float get_plexus_delay ()
{
    float		attack_delay;

    attack_delay = itof(F_MONK_PLEXUS_DELAY (
        shadow_who->query_skill (MONK_SKILL_PLEXUS),
        shadow_who->query_stat (SS_CON),
        shadow_who->query_stat (SS_WIS)));

    return attack_delay;
}

/*
 * Function name: plexus_message
 * Description:   Describe the result of the plexus
 *
 * Arguments:     pen: the penetration value of the hit
 *                target: the target we hit
 *                armour: the armour that the target is wearing on
 *                    their body
 * Returns:       void
 */
static void
plexus_message(int pen, object target, object armour)
{
    int    arm_ac;
    int    arm_damage;

    /* complete miss    */
    if (pen < 0)
    {
        MSGSW("You aim your open hand at " + TNAME + ", but "
            + THE + " dodges aside.");
        MSGTARG(SWCNAME + " aims for your solar plexus with "
            + SWHIS + " open hand, but you dodge aside.");
        TELLWATCHER(SWCNAME + " aims for the solar plexus of "
            + TNAME + ", but " + THE + " dodges aside.");

        return;
    }
    /* hit, but had no effect.    */
    else if (pen == 0)
    {
        if((objectp(armour)) && ((arm_ac = armour->query_ac()) > 2))
        {
            /* We missed, and the enemy was wearing body armour.    */
            MSGSW("You drive your open hand into " + TNAME + "'s solar "
                + "plexus, but the force is absorbed by "
                + THIS + " " + QSHORT(armour) + ".");
            MSGTARG(SWCNAME + " drives "
                + SWHIS + " open hand into your solar plexus, but "
                + "the force of the blow is absorbed by your "
                + QSHORT(armour) + ".");
            TELLWATCHER(SWCNAME + " drives "
                + SWHIS + " open hand into " + TNAME + "'s solar plexus, but "
                + "the force of the blow is absorbed by " + THIS + " "
                + QSHORT(armour) + ".");

            /* Now damage the player based on the ac of the armour    */
            if(random(arm_ac / 3))
            {
                shadow_who->heal_hp(-(random(arm_ac)));
                TELLSW("Your hand stings from the blow.");
            }

            return;
        }
        else
        {
            /* We missed, and the enemy was not wearing any body armour.    */

            MSGSW("You drive your open hand into " + TNAME + "'s solar "
                + "plexus, but the blow seems to have no effect.");
            MSGTARG(SWCNAME + " drives "
                + SWHIS + " open hand into your solar plexus, but "
                + "the blow seems to have no effect.");
            TELLWATCHER(SWCNAME + " drives "
                + SWHIS + " open hand into " + TNAME + "'s solar plexus, but "
                + "the blow seems to have no effect.");

            return;
        }

    }


    /* Fall through: we hit.
     * 20% chance that we damage armours slighty.
     */
    if((objectp(armour)) && ((arm_ac = armour->query_ac()) > 5) && (random(100) < 20))
    {
        // damage the armour slightly if we manage to break through it.
        // magical armours are damaged much less.
        arm_damage = armour->query_likely_cond() / 10 + 1;
        if (armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
            arm_damage /= 3;
        armour->set_condition(armour->query_condition() + arm_damage);

    }


    /* Normal messages for plexus    */
    TELLWATCHER(SWCNAME + " drives " + SWHIS + " open hand into "
        + TNAME + "'s solar plexus.");

    MSGSW("You strike " + TNAME + "'s solar plexus with your "
        + "open hand, stunning " + THIM + ".");
    MSGTARG(SWCNAME + " strikes your solar plexus with " + SWHIS
        + " open hand. You feel numb.");

    return;
}

/*
 * Function name: do_plexus
 * Description:   the result of the plexus special attack. Decide
 *                if we hit the target, determine the effect of
 *                the attack.
 * Arguments:     target: the target we are trying to hit.
 *                force: always hit (for debugging / statistics gathering)
 * Returns:       array of ({ 1 if hit 0 if miss, stun amount, delay })
 */
varargs mixed
do_plexus(object target, int force = 0)
{
    object   combat_ob,
             stun,
             armour;
    string   text;
    int      i,
             pen,
             ac,
            *hit_ids,
             enemy_armour_ac,
             hit,
             stun_time;
    mixed    why,
            *hitloc,
             plex_resistance;
    float    tt = 0.0;
    int      plexus;
    int      str;
    int      dex;

    attack_alarm = 0;

    // set the time we can next attack
    next_attack_time = time() + (ftoi (get_plexus_delay()) / 2);

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(shadow_who)))
    {
        shadow_who->catch_tell("The target of your attack seems to " +
            "have slipped away.\n");
        return ({ 0, 0, 0 });
    }

    /* Has target become invalid somehow? */
    if ((stringp(why = m_may_special_attack(target, "plexus"))) & (!force))
    {
        shadow_who->catch_tell(why);
        return ({ 0, 0, 0 });
    }


    combat_ob = shadow_who->query_combat_object();


    // check first for body armour, and take it into account
    if (objectp(armour = target->query_armour(TS_TORSO)))
    {
        ac = armour->query_ac();
    }
    // else take the target's body ac
    else if (!(hitloc = combat_ob->query_hitloc(A_BODY)))
    {
        ac = hitloc[HIT_AC][0];
    }
    else // else take an average of all the target's ac's
    {
        hit_ids = combat_ob->query_hitloc_id();
        if (sizeof(hit_ids))
        {
            for (ac = 0, i = 0; i < sizeof(hit_ids); i++)
            {
                ac += combat_ob->query_hitloc(hit_ids[i])[HIT_AC][0];
            }

            ac /= sizeof(hit_ids);
        }
    }

    str = shadow_who->query_stat (SS_STR);
    dex = shadow_who->query_stat (SS_DEX);
    plexus = shadow_who->query_skill (MONK_SKILL_PLEXUS);

    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    hit = combat_ob->cb_tohit(W_ANYH, (query_attack_mod() * MONK_PLEXUS_HIT) / 100, 
        target);
    //hit = (F_MONK_PLEXUS_HIT_CHANCE(plexus,
    //    str, dex,
    //    ac, target->query_stat (SS_DEX))) - random (100);


    // make sure we cannot overlap plex an enemy forever
    if ((target->query_prop (MONK_I_LAST_PLEXXED) + MONK_PLEXUS_MIN_INTERVAL) >
        time ())
    {
        hit = 0;
    }

    if (hit > 0)
    {

        // randomize the ac a little bit: mean value is still original ac
        ac = (ac / 2) + (random(ac));

	stun_time = F_MONK_PLEXUS_STUN_DURATION(plexus, str);

	if (stun_time > F_MONK_PLEXUS_MAX_STUN_DURATION (plexus, str))
	    stun_time = F_MONK_PLEXUS_MAX_STUN_DURATION (plexus, str);

        tt = itof(stun_time);

        // check for plexus resistance in the target
        if (intp(plex_resistance = target->query_prop("_live_m_no_plexus")))
            tt = tt * itof((100 - plex_resistance) / 100);


        stun = present(MONK_PLEXUS_STUN_ID, target);

        if ((tt > 0.0) && !stun)
        {
            setuid();
            seteuid(getuid());

            if (stun = clone_object(MONK_OBJ + "stun"))
            {
                if (stun->move(target, 1))
                    stun->remove_object();
                else
                    stun->start_time(tt);

                // save the last time the creature was plaxxed
                target->add_prop (MONK_I_LAST_PLEXXED, time ());

                //find_living("cirion")->catch_tell ("### Stun time: " + ftoi (tt) + "\n");
            }
        }
    }
    else
    {
        shadow_who->add_panic(1);
        shadow_who->add_attack_delay(5);

        pen = -1;
    }
 
    if (tt <= 0.0)
        hit = 0;

    plexus_message(hit, target, armour);

    add_monk_attack_fatigue();

    return ({ (hit > 0), ftoi(tt), (
        F_MONK_PLEXUS_DELAY (shadow_who->query_skill (MONK_SKILL_PLEXUS),
        shadow_who->query_stat (SS_CON), shadow_who->query_stat (SS_WIS))) });
}

/*
 * Function name: m_start_plexus
 * Description:   begin the special attack, set the alarm
 *                for when the attack will hit.
 * Arguments:     the target of the attack
 * Returns:       void
 */
void
m_start_plexus(object target)
{
    // don't attack ourselves...
    if (shadow_who == target)
    {
        shadow_who->catch_tell("You change your mind and decide "
            + "not to administer a self-plexus.\n");
        return;
    }

    if (time() < next_attack_time)
    {
        shadow_who->catch_tell("You are not yet recovered from your "
            + "last attack.\n");
        return;
    }

    shadow_who->catch_tell("You try to get a chance to hit " +
        target->query_objective() + " in the solar plexus.\n");

    attack_alarm = set_alarm(get_plexus_delay() / 2.0, 0.0, &do_plexus(target));
}


/*
 * Function name: get_strike_weapon
 * Description:   Get the part of the body we used to
 *                strike with. Picks a random attack
 *                part (left leg, right leg, left fist,
 *                right fist). Will check to see if the
 *                player is wielding anything, and if so,
 *                will not attack with that hand(s).
 * Arguments:     who - the object for whom to check.
 * Returns:       the string that describes the attacking
 *                body part.
 */
private nomask varargs string
get_strike_weapon(object who = this_player())
{
    string *strs;


    strs = ({ MDESC_FOOT_LEFT, MDESC_FOOT_RIGHT });

    /* check to see if they are wielding something         */
    /* in both hands. If not, check each individual hand.  */
    if (!objectp(who->query_weapon(W_BOTH)))
    {
        if (!objectp(who->query_weapon(W_LEFT)))
            strs += ({ MDESC_FIST_LEFT });

        if (!objectp(who->query_weapon(W_RIGHT)))
            strs += ({ MDESC_FIST_RIGHT });
    }

    /* return a randon attack    */
    return strs[random(sizeof(strs))];
}


private nomask varargs int
query_strike_high_low (string with, string where)
{
    /* HIGH */
    if (with == "left fist" || with == "right fist")
    {
        if (where == "legs")
            return MST_HIGH_TO_LOW;
        else
            return MST_HIGH_TO_HIGH;
    }
    else /* LOW */
    {
        if (where == "legs")
            return MST_LOW_TO_LOW;
        else
            return MST_LOW_TO_HIGH;
    }
}


static void
strike_message_all(object target, int phurt, string hitloc, int phit, int dam, int jux, string with)
{
    string      prefix, prefixp, vb, vbp, me_pre, other_pre;
    int         rand;
    string      possessive;

    /* make the hitloc description prettier.    */
    hitloc = m_translate_hitloc (hitloc);

    if(phurt < -1)
        phurt = -1;


    possessive = this_player()->query_possessive();

    switch (jux)
    {
        case MST_HIGH_TO_LOW:
            rand = random(4);
            prefix = (({ "Ducking down,", 
                "Executing a quick "
                + "roll on the ground,", 
                "With a quick downward jab,",
                "Crouching down," }))[rand];
            prefixp = (({ "Ducking down,", 
                "Executing a quick "
                + "roll on the ground,", 
                "With a quick downward jab,",
                "Crouching down," }))[rand];

            break;
        case MST_HIGH_TO_HIGH:
            rand = random(2);
            prefix = (({ "Spinning around,", 
                "Executing a deft spin "
                + "on the balls of your feet," }))[rand];
            prefixp = (({ "Spinning around,", 
                "Executing a deft spin "
                + "on the balls of " + possessive + " feet," }))[rand];

            break;
        case MST_LOW_TO_LOW:
            rand = random(2);
            prefix = (({ "With a sweeping motion,",
                "Dropping to the ground," }))[rand];
            prefixp = (({ "With a sweeping motion,",
                "Dropping to the ground," }))[rand];

            break;
        case MST_LOW_TO_HIGH:
            prefix = "";
            break;

    }

    switch (phurt)
    {
        case -1: // complete miss
            vb = "miss";
            vbp = "misses";
            break;
        case 0: // hit, but little damage
            vb = "brush";
            vbp = "brushes";
            break;
        case 1 .. 2:
            vb = "brush";
            vbp = "brushes";
            break;
        case 3 .. 4:
            vb = "bruise";
            vbp = "bruises";
            break;
        case 5..9:
            if((with == MDESC_FOOT_RIGHT) || (with == MDESC_FOOT_LEFT))
            {
                vb = "kick";
                vbp = "kicks";
            }
            else
            {
                vb = "punch";
                vbp = "punches";
            }
            break;
        case 10..19:
            vb = "strike";
            vbp = "strikes";
            break;
        case 20..29:
            vb = "slam";
            vbp = "slams";
            break;
        case 30..49:
            vb = "smash";
            vbp = "smashes";
            break;
        case 50..69:
            vb = "crush";
            vbp = "crushes";
            break;
        case 70..89:
            vb = "crush";
            vbp = "crushes";
            break;
        default:
            vb = "crush";
            vbp = "crushes";
    }


    if(strlen(prefix))
    {
        me_pre = prefix + " you " + vb + " ";
        other_pre = prefixp + " " + SWNAME + " " + vbp + " ";
    }
    else
    {
        me_pre = "You " + vb + " ";
        other_pre = SWCNAME + " " + vbp + " ";
    }

    /* Normal messages for plexus    */
    MSGSW(me_pre + QTPNAME(target) + " " + hitloc + " with your " + with + ".");
    TELLWATCHER(other_pre + QTPNAME(target) + " " + hitloc
        + " with " + SWHIS + " " + with + ".");
    MSGTARG(other_pre + "your " + hitloc
        + " with " + SWHIS + " " + with + ".");
    return;
}

static void
strike_message_humanoid(object target, int phurt, string hitloc, int phit, int dam)
{
    string with;
    int jux;

    with = get_strike_weapon ();
    jux = query_strike_high_low (with, hitloc);

    strike_message_all(target, phurt, hitloc, phit, dam, jux, with);
}

static void
strike_message_non_humanoid(object target, int phurt, string hitloc, int phit, int dam)
{
    string with;

    with = get_strike_weapon ();

    strike_message_all(target, phurt, hitloc, phit, dam, MST_NONE, with);
}

/*
 * Function name: strike_message
 * Description:   give the description of the strike special
 *                attack
 * Arguments:     target: the target we hit
 *                phurt: the percentage of the target's remaining hp we took away
 *                hitloc: the hitloc we struck
 *                phit: the percentage of success we had
 *                dam: the amout of damage we did in hp
 * Returns:       void
 */
static void
strike_message(object target, int phurt, string hitloc, int phit, int dam)
{
#ifdef DEBUG_COMBAT
    m_tell_guild_masters ("mstrike with the following result: " + phurt
        + ", " + hitloc + ", " + phit + ", " + dam + "\n", 10);
#endif

    if (target->query_humanoid())
        strike_message_humanoid(target, phurt, hitloc, phit, dam);
    else
        strike_message_non_humanoid(target, phurt, hitloc, phit, dam);
}


/*
 * Function name: do_strike
 * Description:   perform the strike special attack.
 *
 * Arguments:     target: the target we are trying to hit.
 *                hit_id: (optional) the hitloc id of the
 *                    enemy we are trying to hit.
 *                forced: hit regardless of delays, etc. (for testing)
 * Returns:       array of ({ 1 if hit 0 if miss, pen, delay })
 */
varargs mixed
do_strike(object target, int hit_id = -1, int forced = 0)
{
    object  combat_ob;
    int     pen,
            phurt,
            hitsuc;
    mixed   why,
            strike_resistance,
           *hit_result;
    int     wis;
    int     dex;
    int     str;
    int     strike;

    attack_alarm = 0;


    wis = shadow_who->query_stat (SS_WIS);
    dex = shadow_who->query_stat (SS_DEX);
    str = shadow_who->query_stat (SS_STR);
    strike = shadow_who->query_skill (MONK_SKILL_STRIKE);

    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(shadow_who)))
    {
        shadow_who->catch_tell("The target of your attack seems to " +
            "have slipped away.\n");
        return ({ 0, 0, 0});
    }

    /* Has target become invalid somehow? */
    if ((stringp(why = m_may_special_attack(target, "strike"))) && !forced)
    {
        shadow_who->catch_tell(why);
        return ({ 0, 0, 0});
    }

    combat_ob = shadow_who->query_combat_object();
 
    /* Test to see if the attacker hits.  cb_tohit() is the routine
     * used by the combat system to determine if a regular attack
     * hits, but it also works nicely for our purposes.
     */
    if ((hitsuc = combat_ob->cb_tohit(-1, query_attack_mod() * MONK_STRIKE_HIT / 100,
        target)) > 0)
    {
        pen = F_MONK_STRIKE_PEN(str, strike);
        pen = (pen * query_attack_mod()) / 100;

        if (intp(strike_resistance = target->query_prop("_live_m_no_strike")))
    	{
                pen = pen * (100 - strike_resistance) / 100;
    	}

        /* we pass in the hit_id in we specified what part of the    */
        /* body to hit.                                              */
        hit_result = target->hit_me(pen, W_BLUDGEON, shadow_who, -1, hit_id);
    }
    else
    {
        hit_result = target->hit_me(hitsuc, 0, shadow_who, -1, hit_id);
    }

    /* special hitres of 101 to show that the enemy actually died.    */
    if ((target->query_hp()) <= 0)
        hit_result[1] = 101;

    strike_message(target, hit_result [0], hit_result [1],
        hit_result [2], hit_result [3]);

    phurt = hit_result[0];

    if (phurt >= 0)
    {
        shadow_who->add_panic(-3 - phurt / 5);

        if (target->query_hp() <= 0)
        {
            target->do_die(shadow_who);
        }
    }
    else
    {
        shadow_who->add_panic(1);
        shadow_who->add_attack_delay(5); // delay the next strike
    }

    add_monk_attack_fatigue();

    return ({ (hitsuc>0), pen, (F_MONK_STRIKE_DELAY (strike, dex, wis)) });

}

/*
 * Function name: m_start_strike
 * Description:   begin the special attack, set the alarm
 *                for when we will hit.
 * Arguments:     target: the target we are trying to hit.
 * Returns:       void
 */
varargs public void
m_start_strike(object target, int where = -1, string hdesc = "")
{
    string    attack_str, attack_str_other;
    object    cur_target;

    // don't attack ourselves...
    if (shadow_who == target)
    {
        shadow_who->catch_tell("You decide against "
            + "striking yourself.\n");
        return;
    }

    /* start attacking the object we will be striking.    */
    cur_target = shadow_who->query_attack();

    if (target != cur_target)
    {
        shadow_who->attack_object(target);

        if(!objectp(cur_target))
        {
            attack_str = "attack ";
            attack_str_other = "attacks ";
        }
        else
        {
            attack_str = "turn to attack ";
            attack_str_other = "turns to attack ";
        }

        /* give the initiate attack messages.    */
        shadow_who->catch_tell("You " + attack_str + target->query_the_name(shadow_who) + ".\n");
        target->catch_tell(shadow_who->query_The_name(target) + " " + attack_str_other + " you!\n");
        say(QCTNAME(shadow_who) + " " + attack_str_other + QTNAME(target) + ".\n", ({ shadow_who, target }));
    }


    if (!strlen(hdesc))
        shadow_who->catch_tell("You prepare to strike " +
            target->query_objective() + ".\n");
    else
        /* we specified where we want to strike the target.    */
        shadow_who->catch_tell("You prepare to strike " +
            target->query_objective() + " on the " + hdesc + ".\n");

#ifdef DEBUG_COMBAT
    m_tell_guild_masters ("mstrike attempt at: " + where + "\n", 10);
#endif

    attack_alarm = set_alarm(itof(MONK_STRIKE_DELAY), 0.0, &do_strike(target, where));
}

/*
 * Function name: query_monk_special_active
 * Description:   Check to see if the alarm for attacking is
 *                set. If it is, then the shadowed player is
 *                currently either preparing or recovering
 *                from a special attack.
 * Arguments:     none
 * Returns:       1 if we are preparing a special attack,
 *                0 otherwise
 */
int
query_monk_special_active()
{
    return !!attack_alarm;
}

/*
 * Function name: m_query_focus
 * Description:   Check to see if the shadowed player
 *                is currently focused.
 * Returns:       0 if not focused
 */
public int
m_query_focus()
{
    return focus_level;
}

int
m_add_focus(int how_much)
{
    focus_level += how_much;

    if(focus_level < 0)
        focus_level = 0;

    return focus_level;
}

void
m_end_focus()
{
    m_add_focus(-1);
    last_focus = time(); // set the time the last focus ended
    shadow_who->catch_tell("You feel your concentration slipping away.\n");
}

int
m_start_focus()
{
    int duration;


    if(m_query_focus() != 0)
    {
        notify_fail("You are already focusing all your energies as much "
            + "as you can.\n");
        return 0;
    }


    if(shadow_who->query_fatigue() < MONK_FOCUS_FATIGUE_COST)
    {
        notify_fail("You are too weary to focus your energies.\n");
        return 0;
    }

    if(shadow_who->query_mana() < MONK_FOCUS_MANA_COST)
    {
        notify_fail("You are too exhausted mentally to focus your energies.\n");
        return 0;
    }

    if(shadow_who->query_attack())
    {
        notify_fail("You are too busy fighting to focus your energies.\n");
        return 0;
    }

    duration = F_MONK_FOCUS_DURATION(shadow_who->query_skill(MONK_SKILL_FOCUS), last_focus);

    if(duration < MONK_FOCUS_MIN_DURATION)
    {
        notify_fail("You cannot seem to gather enough concentration yet.\n");
        return 0;
    }
    else
    {
        shadow_who->add_mana(-MONK_FOCUS_MANA_COST);
        shadow_who->add_fatigue(-MONK_FOCUS_FATIGUE_COST);

        shadow_who->catch_tell("You focus all your energies within yourself, and everything "
            + "around becomes very silent.\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who) + " starts to breathe very slowly and "
            + "a look of concentration and peace fall upon "
            + shadow_who->query_possessive() + " face.\n", shadow_who, shadow_who);

        m_add_focus(1);
        set_alarm(itof(duration), 0.0, m_end_focus);
        return 1;
    }

}


/*
 * Function name: query_guild_skill_name
 * Description:   Return the name of any special guild
 *                skills.
 * Arguments:     type - the skill ID
 * Returns:       The name of the guild skill, or 0 if unrecognized
 */
mixed
query_guild_skill_name(int type)
{
    switch(type)
    {
        case MONK_SKILL_FOCUS:
            return "focus";
        case MONK_SKILL_STRIKE:
            return "strike";
        case MONK_SKILL_PLEXUS:
            return "plexus";
        default:
            // check for other shadow's definitions skills
            return shadow_who->query_guild_skill_name(type);
    }
}


/*
 * Function name: query_monk_shadow
 * Description:   Simple way of obtaining this shadow
 *                object.
 * Returns:       the shadow object
 */
object
query_monk_shadow()
{
    return this_object();
}


/*
 * Function name: query_guild_keep_player
 * Description:   Check to see if we keep the player or
 *                not. Since we do quite a bit of additional
 *                bookkeeping, we handle everything in
 *                the m_login function in init_lay_shadow.
 * Arguments:     who: the player to check for
 * Returns:       1: we always keep the player
 */
int
query_guild_keep_player(object who)
{
    return 1;
}


/*
 * Function name: notify_you_killed_me
 * Description:   This is called each time the monk kills something.
 * Arguments:     ob - the object that was killed
 */
void
notify_you_killed_me(object ob)
{
    string *names = ({ });
    string *n, str;

    shadow_who->notify_you_killed_me(ob);

    /* Yikes! I killed a dragon! 
     */
    if (ob->query_race() == "dragon")
    {
        m_add_punishment(shadow_who, M_PUNISH_DISGRACE);
        m_log(capitalize(shadow_who->query_name()) +" was "+
            "disgraced for killing the "+ ob->short() +".\n");
        m_post_board_msg(capitalize(shadow_who->query_name()) +
            " was disgraced for killing the "+ ob->short() +
            ".\n    Dragons are sacred!\n");
        return;
    }

    if (interactive(ob))
    {
        /* Monks should not be disgraced for defending their home.
         */
        str = file_name(environment(ob));
        if (str[..23] == "/d/Genesis/guilds/monks/")
        {
            shadow_who->catch_msg("\nThis death at your hands "+
                "will not be punished, for it was in defence of "+
                "the monastery.\n");
	  return;
        }

        /* I killed a fellow monk :(
         */
#if 0
// Cir: I am not sure what the below is meant to do...
        if (m_query_monk(ob, SS_OCCUP) ||
            m_query_monk(ob, SS_LAYMAN) &&
	  member_array(ob, q_att_ob()) >= 0)
#endif
        if (m_query_monk(ob, SS_OCCUP) ||
            m_query_monk(ob, SS_LAYMAN))
        {
            m_add_punishment(shadow_who, M_PUNISH_DISGRACE);
            m_log(capitalize(shadow_who->query_name()) +" was "+
                "disgraced for killing the monk named "+ 
                capitalize(ob->query_name()) +".\n");
            m_post_board_msg(capitalize(shadow_who->query_name()) +
                " was disgraced for killing the monk named "+ 
                capitalize(ob->query_name()) +".\n");
            return;
        }      

        /* I killed a regular player and I didn't mwarn.
         */
        names = shadow_who->query_prop(MONK_HAS_WARNED);
        n = ob->query_real_name();
        if (member_array(n, names) == -1)
        {
            m_add_punishment(shadow_who, M_PUNISH_DISGRACE);
            m_log(capitalize(shadow_who->query_name()) +" was "+
                "disgraced for killing the "+ ob->short() +" named "+
                capitalize(ob->query_name()) +".\n");
            m_post_board_msg(capitalize(shadow_who->query_name()) +
                " was disgraced for killing the "+ ob->short() +
                " named "+ capitalize(ob->query_name()) +" without "+
                "using mwarn.\n");
            return;
        }
       /* I killed someone I did mwarn and its ok :) */       
    }
}


/*
 * Function name: query_def_post
 * Description:   Returns the name of the default post
 *                office for this player.
 * Returns:       The path to the PO file
 */
public string
query_def_post() 
{ 
    return MONK_ROOM + "post";
}



