/*
 * /d/Sparkle/area/jade/obj/throwable_item.c
 * Inherit this module to make an object throwable. Be sure to include the
 * following to make the throw command available:
inherit "/d/Sparkle/area/jade/obj/throwable_item.c" as throwable;

void init()
{
    ::init();
    init_throwable();
}

//Also, holdable_item has some requirements:
void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    leave_env_throwable(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_throwable(num);
}

 *
 * By default, this provides a throwing action that can be directed at animate
 * (full sequence of combat checks) or inanimate (basic skill check and effect).
 * Relevant stats are str and dex, skills are missiles and (for piercing bonus)
 * javelin (awareness for dodging).
 * (thanks go to Finwe and prior developers of /d/Shire/common/obj/rock.c).
 * You can customize the checks and hit/miss effects or override particular
 * steps or the overall sequence.
 *
 * Though a thrown object can be considered a projectile, throwable_item is
 * specifically for hand throwing - no launcher, short range, possible for
 * /std classes which conflict with projectile.c (e.g. herbs) or could never be
 * loaded into a ranged weapon (tables).
 *
 * Thanks go to Finwe and prior developers of /d/Shire/common/obj/rock.c, and of
 * /std/launch_weapon.c.
 *
 * Martin Berka (Mar), 2017-02-05 Sparkle
 */

#pragma no_clone
#pragma save_binary
#pragma strict_types

inherit "/lib/holdable_item"; //To throw something, you must hold it.

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <ss_types.h> //Skills
#include <tasks.h>

/* Global variables */
string  Missile_name,   /* Thanks to heap, too complicated to handle normally */
        Throw_command;  /* The command word used to throw. */

object  Missile,        /* Item being thrown - not necessarily this_object()*/
        Thrower,        /* Throwing the throwable_item, not throwing up */
        Target;         /* The Target which the Thrower attempts to hit. */

mixed   Hitloc_id;      /* The hitloc we aim at. */
int     Throw_alarm,    /* Alarm used between lift and throw. */
        Throwing;       /* Flag - throwing in progress */

/* Definitions */
#define ENV     environment
#define HE_SHE query_pronoun()
#define HIM_HER query_objective()
#define HIS_HER query_possessive()
#define TO      this_object()


/*
 * Function:    aim_check
 * Description: Determine how accurately Missile is thrown
 * Arguments:   (int) Surface of Target facing Thrower, in cm^2.
 * Returns:     (int) 1 if necessary slots clear, otherwise 0
 */
varargs int
aim_check(int target_front_surface = 25)
{
    int noticeable_surface = 25; //A 5-cm square should be visible across a room
    //How well can each be made out?
    int target_view_size = max(1, target_front_surface / noticeable_surface);

    return Thrower->resolve_task(TASK_ROUTINE + 100 / target_view_size,
        ({ TS_DEX, SKILL_WEIGHT, 40, TS_DIS, SKILL_WEIGHT, 40, SS_WEP_JAVELIN,
        SKILL_WEIGHT, 20, SS_WEP_MISSILE }));
}


/*
 * Function:    hand_check
 * Description: Check whether living has the hands to throw or catch item.
 *              If yes, occupy them until further notice.
 * Arguments:   (object) living that slots clear, otherwise 0
 * Returns:     (int) 1 if necessary slots clear, otherwise 0
 */
int
hand_check(object checked_living)
{
    mixed val;
    if (stringp( val = checked_living->occupy_slot(Missile) ))
    {
        if (checked_living == Thrower)
        {
            checked_living->catch_msg(val);
        }
        return 0;
    }
    Target->empty_slot(Missile);
    return 1;
}

/*
 * Function:    range_check
 * Description: Check how much farther (positive) or less than (negative) the
 *      distance to Target the Missile could travel without obstacles
 * Returns:     (int) Percent success (positive) / failure (negative)
 */
int
range_check()
{
    int weight_difficulty = Missile->query_prop(OBJ_I_WEIGHT) / 2000
        + Thrower->query_encumberance_weight() / 500;
    return Thrower->resolve_task(TASK_SIMPLE + weight_difficulty,
        ({ TS_STR, SKILL_WEIGHT, 40, SS_WEP_JAVELIN, SKILL_WEIGHT, 10,
        SS_WEP_MISSILE }));
}


/*
 * Function:    throw_damage_check
 * Description: Determine damage caused if item hit a living, factoring in
 *      armour and pressure (range, mass, volume)
 * Arguments:
 * Returns:     (int) The damage [hp]
 */
int
throw_damage_check(int item_mass)
{
    mixed hitloc, *hitlocs;
    int wc_pen;

/*    hitlocs = Target->query_combat_object()->query_hitloc_id();
	if (!sizeof(hitlocs))
	{
            tell_object(Thrower, "You don't find any " + location + " on " +
			Target->query_the_name(Thrower) +
			" to " + query_verb() + " at.\n");
	    return -1;
	}

	for (i = 0; i < sizeof(hitlocs); i++)
	{
            hitloc = Target->query_combat_object()->query_hitloc(hitlocs[i]);

	    if (location == hitloc[2])
	    {
                Hitloc_id = hitlocs[i];
	        break;
	    }
	}

	if (i >= sizeof(hitlocs))
	{
        tell_object(Thrower, "You don't find any " + location + " on " +
                Target->query_the_name(Thrower) +
                " to " + query_verb() + " at.\n");
            return -1;
        }
    }
    */


    int skill = Thrower->query_skill(SS_WEP_MISSILE);
    if (skill < 7)
        skill = 7;

        wc_pen = item_mass / 50;

        if (wc_pen > 40) wc_pen = 40;
        if (wc_pen < 1) wc_pen = 1;

    return Target->hit_me(F_PENMOD(wc_pen, skill), W_BLUDGEON, Thrower, -1);
}


/*
 * Function:    dodge_movement_check
 * Description: Check how far the Target moves to dodge. Target will usually
 *      at least flinch away, but if the awareness check is low enough, then it
 *      could decrease the distance between missile path and self.
 * Arguments:   (int) milliseconds to react
 * Returns:     (int) The distance that the Target moves - negative is to the
 *      (thrower's) left, positive to the right, neglecting jump and duck. [cm]?
 */
int
dodge_movement_check(int time_to_react)
{
    /* Max dodge of 3m in 1s, like a great standing long jump or two big steps -
    many unpredictable conditions, so random based on time and dex. Above 1s,
    Target picks up speed and "runs" - will dodge basically anything.*/
    time_to_react -= max(300, 1200 - 9 * Target->query_skill(SS_AWARENESS));
    /*http://www.visualexpert.com/Resources/reactiontime.html
    Maximum based on a surprised driver. Minimum a compromise between the 500 of
    driver who expected and the 100 of a particularly sudden runner who had
    many seconds to tense to respond to a sound (planned response to visual
    takes at least 150). */

    if (time_to_react < 1) //Ran out of time to start moving
    {
        return 0;
    }

    if (time_to_react < 300) //Starts moving, still picking up speed
    {
        return random(time_to_react * Target->query_stat(SS_DEX) / 200);
    }

    if (time_to_react < 1000)
    {
        return random(time_to_react * Target->query_stat(SS_DEX) / 100);
    }

    return random(time_to_react * Target->query_stat(SS_DEX) / 50);
}


/*
 * Function:    aim_at_living
 * Description: Notify everyone of pending attack, start combat, schedule throw
 * Returns:     (int) 1 Success / 0 Fail (aim blocked)
 */
int
aim_at_living(object Thrower, object Target)
{
    if (Thrower->query_prop(LIVE_I_CONCENTRATE))
    {
        notify_fail("You are too busy with other things to throw right now.\n");
        return 0;
    }

    if (!F_DARE_ATTACK(Thrower, Target))
    {
        notify_fail("You do not dare attack " + Target->short() + "!\n");
        return 0;
    }

    // Cannot throw at linkdead
    if (interactive(Target) && Target->query_linkdead())
    {
        tell_object(Thrower, "You will have to wait for " +
		    Target->query_the_name(Thrower) +
		    " to return from link death first.\n");
        return 0;
    }

    if (Thrower->query_prop(LIVE_I_STUNNED))
    {
        tell_object(Thrower, "You cannot " + Throw_command +
            " while stunned.\n");
        return 0;
    }

	Thrower->catch_msg("You prepare to throw the " + Missile_name + " at " +
        QTNAME(Target) + "!\n");

    /*Assume that other people in the room see from different angles and
    will know what is thrown.*/
    if (Target->can_see_in_room())
    {
        Target->catch_msg(Thrower->query_The_name() + " is about to throw "
            + " something at you!\n");
    }

    object *bystanders;
    bystanders = FILTER_LIVE(all_inventory(environment(Thrower))) - ({Thrower});
    bystanders = filter(FILTER_IS_SEEN(Thrower, bystanders),
        &->can_see_in_room());
    if (sizeof(bystanders))
    {
        bystanders->catch_msg(QCTNAME(Thrower) + " aims " + Thrower->HIS_HER
            + " " + Missile_name + " at " + QTNAME(Target) + ".\n");
    }

    //Remainder will be handled in combat
	Thrower->add_prop(LIVE_O_SPELL_ATTACK, Missile);
	Thrower->attack_object(Target);
    //Spell attack waits up to 5 s by default; temporarily double Thrower speed.
    Thrower->add_prop(LIVE_I_QUICKNESS, 250);

    //Range due to throwing: thrown item should get the first hit.
    /*Thrower is presumably not throwing at someone right next to them and if
    necessary uses the delay to position themselves at a reasonable distance.
    Target charges as soon as they realize what is happening, but will not reach
    Thrower before Missile hits. None of this applies if Target is already
    fighting Thrower: immediately adjacent and no way for Thrower to distance.*/
    if (Target->query_attack() != Thrower)
    {
        Target->add_attack_delay(10);
    }

	return 1;
}


/*
 * Function name: impact_effect
 * Description  : What if item suddenly decelerates against a hard surface?
 *          Override for effect ignoring whether throw hit or using proximity
 * Arguments    : (object) nearest object to the place where Missile stops.
 * Returns      : (int) 1 if effect occurred, 0 if blocked by some extra
 *      condition
 */
varargs int
impact_effect(object nearest = Missile)
{
    tell_room(ENV(Thrower), "The " + Missile_name + " falls to the ground.\n");
    Missile->move(ENV(Thrower), 1); /* And drop on the floor */

    /*  if (nearest_object == Missile) {}
     *  else {}
     */

    return 1;
}


/*
 * Function name: hit_object_effect
 * Description  : What happens if hit?
 * Arguments    : (int) How accurately Target was hit - default 1, barely
                  (int) Percent: how hard Target was hit - default 1, weakly
 * Returns      : (int) 1 if effect occurred, 0 if blocked by some extra
 *      condition
 */
int
hit_object_effect(int percent_accurate = 1, int percent_speed = 1)
{
    Thrower->catch_msg("You throw the " + Missile_name + " at "
        + Target->query_the_name() + " and hit it.\n");
    say(QCTNAME(Thrower) + " throws a " + QTNAME(Missile) + " at " +
        QTNAME(Target) + " and hits it.\n", ({Target,Thrower}));

    impact_effect(Target);
}


/*
 * Function name: miss_effect
 * Description  : What happens if missed?
 * Arguments    : (int) Percent missed - 0 is barely, 100 is ridiculously off.
 * Returns      : (int) 1 if effect occurred, 0 if blocked by some extra
 *      condition
 */
int
miss_effect(int percent_missed)
{
    Thrower->catch_msg("You throw the " + Missile_name + " at " +
        Target->query_the_name() +  " but miss " + Target->HIM_HER + ".\n");
    Target->catch_msg(Thrower->query_The_name()  + " throws a " + Missile_name
        + " at you but misses.\n");
    say(QCTNAME(Thrower) + " throws a " + Missile_name + " at "
        + QTNAME(Target) + " but misses " + Target->HIM_HER + ".\n",
        ({Thrower, Target}));

    if (percent_missed < 50)
    {
        impact_effect(Target);
    }
    else
    {
        impact_effect();
    }
    return 0;
}


/*
 * Function     : hit_living_effect
 * Description  : What happens if hit?
 * Arguments    : (int) How accurately Target was hit - default 1, barely
                  (int) Percent: how hard Target was hit - default 1, weakly
 * Returns      : (int) 1 if effect occurred, 0 if blocked inside function
 */
varargs int
hit_living_effect(int percent_accurate = 1, int percent_speed = 1)
{
    int weight = Missile->query_prop(OBJ_I_WEIGHT);

    if (living(Target))
    {
        mixed res = throw_damage_check(weight);
        string how;

        if (res[0] > 40)
        how = " extremely hard.";
        else if (res[0] > 25)
        how = " very hard.";
        else if (res[0] > 12)
        how = " hard.";
        else
        how = ".";

        Target->catch_msg(Thrower->query_the_name(Target) + " throws a "
            + Missile_name + " at you and hits you" + how + "\n");
        say(QCTNAME(Thrower) + " throws a " + Missile_name + " at "
            + QTNAME(Target) + " and hits " + Target->HIM_HER + how + "\n",
            ({Target, Thrower}));
        Thrower->catch_msg("You throw the " + Missile_name + " at "
            + Target->query_the_name(Thrower) + " and hit "
            + Target->HIM_HER + how + "\n");

        impact_effect(Target);

        return res;
    }
    else
    {
        return 0; //Livings respond to combat, inanimate may not respond at all
    }
}


/*
 * Function     : block_effect
 * Description  : What if Target blocks Missile?
 * Arguments    : (int) Percent: how well Target blocked Missile: 0 means
        barely blocking contact with the body, 100 - easily flinging it aside
                  (object) The item used for blocking.
 * Returns      : (int) 1 if the effect occurred, 0 if blocked by some cond.
 */
varargs int
block_effect(int percent_blocked, object block_item = Missile)
{
    string block_name = "";
    if (block_item == Missile)
    {
        block_name = "";
    }

    Thrower->catch_msg("You throw the " + Missile_name + " at " +
        Target->query_the_name() +  " but " + Target->HE_SHE + " blocks it"
        + (block_name != "" ? " with " + Target->HIS_HER + " " + block_name :"")
        + ".\n");
    Target->catch_msg(Thrower->query_The_name()  + " throws a " + Missile_name
        + " at you, but you block it"
        + (block_name != "" ? " with " + Target->HIS_HER + " " + block_name :"")
        + ".\n");
    say(QCTNAME(Thrower) + " throws a " + Missile_name + " at " + QTNAME(Target)
        + ", who blocks it"
        + (block_name != "" ? " with a " + QTNAME(block_item) : "")
        + ".\n", ({Thrower, Target}));

    //It will take an amazing deflection for item to not land nearby
    if (percent_blocked < 90)
    {
        impact_effect(Target);
    }
    else
    {
        impact_effect();
    }

    return 1;
}


/*
 * Function     : catch_effect
 * Description  : What if Target catches Missile?
 * Arguments    : (int) Percent: how well Target caught Missile: 100 means
        a catch so smooth the Missile did not notice, 0 means barely preventing
        Missile from reaching targeted area.
 * Returns      : (int) 1 if the effect occurred, 0 if blocked by some cond.
 */
int
catch_effect(int percent_caught)
{
    Thrower->catch_msg("You throw the " + Missile_name + " at "
        + Target->query_the_name() +  " but " + Target->HE_SHE
        + " catches it.\n");
    Target->catch_msg(Thrower->query_The_name()  + " throws a " + Missile_name
        + " at you, but you catch it.\n");
    say(QCTNAME(Thrower) + " throws a " + Missile_name + " at " + QTNAME(Target)
        + ", who catches it.\n", ({Thrower, Target}));

    int catch_hurts_below;
    if (!function_exists("query_wt", Missile))
    {
        catch_hurts_below = 0;
    }
    switch (Missile->query_wt())
    {
        case W_JAVELIN: //Long handles, plenty of safe spots to grab.
        case W_POLEARM:
            catch_hurts_below = 10;
            break;
        case W_MISSILE:
            catch_hurts_below = 20; //Shorter, avoid the tip.
            break;
        case W_SWORD:
            catch_hurts_below = 70; //A sword is mostly blade.
            break;
        case W_KNIFE:
            catch_hurts_below = 50; //A sword is mostly blade.
            break;
        case W_CLUB:
        case W_AXE:
            catch_hurts_below = 30;
            break;
        default: //Limited sharp area?
            catch_hurts_below = 20;
    }
    if (Missile->query_prop(OBJ_I_BROKEN))
    {
        catch_hurts_below += 10; //The broken boundary is likely sharp.
    }

    if (percent_caught < catch_hurts_below)
    {

    }

    if (percent_caught < 10) //A bad catch is a sudden stop.
    {
        impact_effect(Target);
        if (!present(Missile_name, Target)) //If impact destroys item, stop here
        {
            return 1;
        }
    }

    Missile->move(Target, 1); //One way or another, Target caught it.

    //Catching should not serve as backdoor giving.
    if (Target->query_prop(LIVE_M_NO_ACCEPT_GIVE))
    {
        Target->command("drop " + Missile_name);
    }

    return 1;
}

/*
 * Function     : dodge_effect
 * Description  : What if the Target dodges the item?
 * Arguments    : (int) Percent by which Target avoided Missile: 0 means barely,
            1 that Missile flew wide. Consider throw accuracy when supplying.
 * Returns      : (int) 1 if the effect occurred, 0 if blocked by some cond.
 */
int
dodge_effect(int percent_blocked)
{
    Thrower->catch_msg("You throw the " + Missile_name + " at " +
        Target->query_the_name() +  " but " + Target->HE_SHE + " dodges.\n");
    Target->catch_msg(Thrower->query_The_name()  + " throws a " + Missile_name
        + " at you, but you dodge it.\n");
    say(QCTNAME(Thrower) + " throws a " + Missile_name + " at " + QTNAME(Target)
        + ", who dodges out of the way.\n", ({Thrower, Target}));

    impact_effect(Target);

    if (percent_blocked < 50)
    {
        impact_effect(Target);
    }
    else
    {
        impact_effect();
    }

    return 1;
}




/*
 * Function     : fall_short_effect
 * Description  : What if the item hits the ground before reaching the Target?
 * Arguments    : Percent of the way that item got from Thrower to Target
 * Returns      : (int) 1 if the effect occurred, 0 if blocked by some cond.
 */
int
fall_short_effect(int percent_short)
{
    Thrower->catch_msg("The " + Missile_name
        + " is too heavy and falls short of " + QCTNAME(Target));
    Target->catch_msg(QCTNAME(Thrower) + "'s throw does not reach you.\n");
    tell_room(ENV(Thrower), QCTNAME(Thrower) + "'s throw falls short of "
        + QCTNAME(Target) + ".\n", ({ Thrower, Target }));

    if (percent_short < 34)
    {
        impact_effect(Thrower);
    }
    else if (percent_short < 67)
    {
        impact_effect();
    }
    else
    {
        impact_effect(Target);
    }

    return 1;
}

/*
 * Function     : front_surface_correction
 * Description  : Correct the front surface of object
 * Arguments    : (int) Area to be corrected
 * Returns      : (int) Modified area
 */
int
front_surface_correction(int object_front)
{
    if (!function_exists("query_wt", Missile))
    {
        return object_front;
    }
    switch (Missile->query_wt())
    {
        case W_JAVELIN:
            return object_front / 25;
            /* Olympic javelin: 270cm, 2.5cm diam -> 1325ml -> 121 cm^2 by
            cube model, vs 5.0 cm^2 based on diameter. Ratio. */
        case W_MISSILE:
            /* Assuming simple arrow: 80 cm, 1 cm diam -> 0.79 cm actual,
            15.8 cube; 0.05 */
            return object_front / 20;
        case W_POLEARM:
            /*Heavy lance:http://www.classicalfencing.com/mcweaponslance.php
            3.5m, 5cm diam -> 20 actual, 361 cube -> 0.06 */
            return object_front /16;
        case W_SWORD:
            /* http://jan.ucc.nau.edu/wew/fencing/blades.html
            One-handed: rapier, 125 cm, 2cm blade diam (3.1 cm2), but
            point-first projection is at least quadrupled by hand-guard ->
            14 cm^2. Guard adds maybe a 1-cm layer to a 392 cm3 volume, for
            406cm3 and 55cm2 cube-model projection; 0.25 */
            return object_front / 4;
            /*Two-handed: 155cm, blade 6.25cm wide, maybe 1 cm thick on avg,
            volume estimate gives 98.8 cm3 if we add 14 cm3 for the guard.
            Good luck throwing a two-handed point-first; this one will spin
            end-over-end, presenting rectangle of 1.25cm (remember handle)
            x (20-155)cm = 109 cm2.
            So pretty close. */
            return object_front * 11 / 10;
        case W_KNIFE:
            /*Based on Fairbairn-Sykes - 6 cm^2 doubles with guard to 12;
            29cm long, volume maybe 174cm3->31 cube model. This is a large
            model -> cutting 0.39 to 0.35 */
            return object_front / 3;
        case W_AXE:
            /*Fanning part of blade 13x9x2 (median values over
            head length) for volume of 234, add a 40cm, 4cm diam. handle for
            737cm3 -> 82cm2 cube model surface. End-over-end spinning will
            present a rectangle of 4 x (18-44, mean 31) = 124,
            long, total 44cm wide.*/
        case W_CLUB:
            /*Hard to calculate, but should not be any more aerodynamic than
            an axe*/
            return object_front * 3 / 2;
        default:
            /*No information about the shape, so no assumptions about how
            it hits the air.*/
            return object_front;
    }
}


/*
 * Function:    pre_throw_check
 * Description: Check prerequisites before throwing
 * Arguments:   (string) rest of command after verb
 *              (int) whether to display failure messages (optional)
 * Returns:     (int) 1 if valid Target identified and set, else 0
 */
varargs int
pre_throw_check(string str, int notify = 1)
{
    string tmp, what;
    object to, room, env;

    //Prevent multiple actions and overwriting of the Missile
    if (Thrower->query_prop(LIVE_O_SPELL_ATTACK))
    {
        if (notify) notify_fail("You are busy attacking!\n");
        return 0;
    }

    if (environment() != Thrower)
    {
        if (notify) notify_fail("First get the " + Missile_name + ".\n");
        return 0;
    }

    room = environment(Thrower);
    if (this_object()->query_prop(HEAP_I_IS)) //Split from heap if applicable
    {
        object missile_heap = this_object();
        object env = environment(missile_heap);
        missile_heap->split_heap(1);
        Missile = missile_heap;
        missile_heap = missile_heap->force_heap_split();
        //Need two heaps to remain in inventory

        missile_heap->move(env, 1);
        Missile_name = Missile->singular_short();
    }
    else
    {
        Missile = this_object();
        Missile_name = Missile->short();
    }

    if (!Missile->query_held()) //If not held already, hold it.
    {
        if (Missile->command_hold() != 1)
        {
            Thrower->catch_msg("You must hold the " + Missile_name
                + " to throw it.\n");
            return 0;
        }
    }

    //Now establish where and what we are throwing
    if (!str) //Throw into an empty space - hard to mess that up.
    {
        impact_effect();
        return 1;
    }

    //Separate missile from target
    if (!sscanf(str, "at %s", tmp) &&
        !sscanf(str, "%s at %s", what, tmp) &&
        !sscanf(str, "%s at %s", what, tmp))
    {
        if (notify) notify_fail("Throw at something or someone.\n");
        return 0;
    }

    //Trying to throw something other than Missile
    if (stringp(what) && !Missile->id(what))
    {
        if (notify) notify_fail("Throw what?\n");
        return 0;
    }

    //Parse and verify single Target
    str = lower_case(tmp);
    mixed oblist = PARSE_COMMAND(str, all_inventory(environment(Thrower)),
       "[the] %i");
    if (!oblist)
    {
        notify_fail("You find no such thing.\n");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        notify_fail("You cannot throw at " + COMPOSITE_ALL_LIVE(oblist)
            + " at the same time.\n");
        return 0;
    }
    Target = oblist[0];

    if (Target == Thrower) //This is physically possible; not enabling self-harm
    {
        Thrower->catch_msg("It is surprisingly difficult to throw something at "
            + "yourself, but you manage to hurl the " + Missile_name
            + " on the ground right by your feet.\n");
        impact_effect(Thrower); //They asked for it.
        return 0;
    }

    if (NPATTACK(Target)) //Object or room prevents attacking?
    {
        if (notify) notify_fail("You cannot attack that way here.\n");
        return 0;
    }

    return 1;
}


/*
 * Function     : throw_sequence
 * Description  : Evaluate the throw step by step, choosing among outcomes
 * Returns      : (int) 1 (ultimately hit desired target) / 0 (any other result)
 */
int
throw_sequence()
{
    int weight = Missile->query_prop(OBJ_I_WEIGHT);
    this_player()->add_fatigue(-weight / 2000); //One point per 2kg thrown.

    /*Check that Thrower can throw far enough. Assume that it is twice as hard
    to throw something across a room as carry it, and that every other thing
    somehow weighing down Thrower reduces the strength available in their arms.
    Knowledge of throwing helps some, aerodynamics a little. */
    int range_success = range_check();
    if (range_success < 0) //Communicate and respond to the fail
    {
        fall_short_effect(range_success);
        return 0;
    }


/* Impact = mass * (contributed strength / mass). Apply weapon-type damage on
impact, default to bludgeon.
Sequence: Pull back (lifts __ and tenses; throw; near target (wide miss / near
miss / on-target); and hit. Crushing damage will depend on
object weight, pierce capacity (weapon type), hit location vs. armour. Broken
things remain throwable, 1/3 as accurate but 50% sharper.
Outdoor natural might allow two more throws before target gets there.
Urban/default outdoor - one. Indoor - zero. Discipline will allow user to
estimate their range accurately and make full use of it, position their
attacks to avoid trees... CHECK projectile.c range.
*/

/*Point-first throwing gives a high chance of critical pierce damage - based on
SS_JAVELIN. */

    int skill, weight_allow, extra_diff, item_cube_side, target_cube_side;
    string how;

    //Take literal "cube" root to estimate one dimension of item and Target
    item_cube_side = ftoi(pow( itof(Missile->query_prop(OBJ_I_VOLUME)), 0.33 ));

    target_cube_side = ftoi(pow( itof(Target->query_prop(OBJ_I_VOLUME)), 0.33 ));
    /* One dimension of cube with the same volume [cm]; e.g 27,000 ml -> 30 cm*/

    //Facing surfaces of Target and item - pretend they are square
    int item_front = item_cube_side * item_cube_side;
    int target_front = target_cube_side * target_cube_side;
    int noticeable_surface = 25; //A 5-cm square should be visible across a room

    //How far off-center is still a hit?
    int target_margin = target_cube_side + item_cube_side;

    int aim_success = aim_check(item_front);

    if (aim_success < 0)
    {
        //If aim is bad enough, could throw at someone/thing else entirely.
        object *all_nearby = all_inventory(ENV(Thrower)) - ({ Thrower, Target});

        //If there are 20 other objects in the room, bound to throw at one.
        if (aim_success < 5 * sizeof(all_nearby) - 100)
        {
            Target = all_nearby[random( sizeof(all_nearby) )];
            //Estimating surface areas of each seems excessive
        }
        else
        {
            miss_effect(aim_success); //Regular miss
            return 0;
        }
    }

    item_front = front_surface_correction(item_front);
    int item_view_size = item_front / noticeable_surface;

    /* Replaced mini-physics simulation. Using results of range check: an
    item that can fly past the target must be moving faster, leaving less time.
    Also, a more accurately thrown item will require a better dodge. */

    if (!living(Target)) //Target will not try to prevent collision
    {
        hit_object_effect(aim_success, range_success);
        return 1;
    }

    /* To react, Target must first see it coming and quickly predict the
    trajectory. Large objects are easier to track. A wiser Target is more
    experienced and can presumably make better use of the senses. */
    if (Target->can_see_in_room() &&
        ( Target->resolve_task(TASK_ROUTINE - 10 * item_view_size,
        ({ TS_WIS, SS_AWARENESS })) > 0 ))
    {
        /* Target knows where Missile is going but still needs to get out of the
        way quickly; needs good dexterity, low burden; harder to dodge large
        things. */
        int dodge_success = Target->resolve_task(
            TASK_ROUTINE + 10 * item_cube_side + range_success, ({ TS_DEX }) );
        //= dodge_movement_check(reaction_time);
        if (dodge_success > aim_success)
        {
            dodge_effect(dodge_success - aim_success);
            return 0;
        }
        else
        {
            aim_success -= dodge_success; //If it's a bad dodge, more on-target
        }

        /* Last chance to avoid: target can attempt to catch or deflect
        the item, depending on whether or not hands are free. */

        if (hand_check(Target)) //Target tries to catch
        {
            int weight_difficulty = weight / 2000
                + Target->query_encumberance_weight() / 500;
            int catch_success = Target->resolve_task(
                TASK_ROUTINE + weight_difficulty, ({ TS_STR, TS_DEX }));;
            if (catch_success > 0)
            {
                catch_effect(catch_success);
                return 0;
            }
        }
        else //Target tries to block with something they are carrying
        {
            object *available_weapons = Target->query_weapon(-1);
            object blocking_weapon = available_weapons[0];
            int block_front = ftoi(pow(
                itof(Missile->query_prop(OBJ_I_VOLUME)), 0.66 ));

            /* Harder to deflect heavy things, and things larger than the
             * blocking item
             */
            int block_difficulty = weight / 2000 - 100 * block_front / item_front
                + Target->query_encumberance_weight() / 100;
            int block_success = Target->resolve_task(TASK_ROUTINE
                + block_difficulty, ({ TS_STR, SS_DEFENCE, SS_PARRY }));;
            if (block_success > 0)
            {
                block_effect(block_success);
                return 0;
            }
        }
    }

    //If still here, Target was hit
    hit_living_effect(aim_success, range_success);
    return 1;
}


/*
 * Function     :    spell_attack
 * Description  : Throwing at living is considered hostile, works as a spell.
 * Arguments    : (object) attacker (thrower - only here for compatibility)
 *                (object) defender (thrower - only here for compatibility)
 * Returns      : (int) 1 Success / 0 Fail (displays message message)
 */
void
spell_attack(object thrower, object target)
{
    //Thrower was given increased speed to avoid waiting for this.
    Thrower->add_prop(LIVE_I_QUICKNESS, 0);

    Throwing = 1;
    throw_sequence();
    Throwing = 0;
}


/*
 * Function:    do_throw
 * Description: Standard throw sequence that calls the various segments
 * Returns:     (int) 1 - action was recognized.
 */
int
do_throw(string str)
{
    int result;

    Thrower = this_player();

    if (!pre_throw_check(str))
    {
        return 1; //Only return 0 for failure to recognize the action.
    }

    if (living(Target))
    {
        result = aim_at_living(Thrower, Target);
    }
    else
    {
        Throwing = 1;
        result = throw_sequence();
        Throwing = 0;
    }
    return 1;
}


/*
 * Function name: leave_env
 * Description  : Carry-over from holdable_item.c
 * Arguments    : (object) What it is leaving
 *                (object) where it is going
 */
void
leave_env_throwable(object from, object to)
{
    //::leave_env(from, to);
    holdable_item_leave_env(from, to);
}


/*
 * Function name: appraise_object
 * Description  : Carry-over from holdable_item.c
 * Arguments    : (int) Appraisal skill
 */
void
appraise_throwable(int num)
{
    //::appraise_object(num);
    appraise_holdable_item();
}

/*
 * Function name: release
 * Description  : Override of holdable_item: block release message when throwing
 * Returns      : (int) - code corresponding to /lib/holdable_item.c release()
 */
int
release()
{
    if (Throwing)
    {
        return 1; //Block release message if throwing
    }
    return 0; //The item can be released, print default messages.
}


/*
 * Function:    init_throwable_item()
 * Description: Add the "throw" command to a player. Since this module is used
 *      in multiple inheritance, this should be called explicitly from the
 *      object's init().
 */
void
init_throwable()
{
    //Add the command to make this throwable
    if (!stringp(Throw_command) || !Throw_command)
    {
        Throw_command = "throw";
    }
    add_action(do_throw, Throw_command);

    //Define the hands necessary to throw it (and hold it)
    int weight = Missile->query_prop(OBJ_I_WEIGHT);
    int capacity = 10 + Thrower->query_stat(SS_STR);
    if (weight > capacity / 4) //Pretty generous
    {
        Missile->set_slots(W_BOTH);
    }
    else
    {
        Missile->set_slots(W_ANYH);
    }
}

/*
 * Function     : query_missile()
 * Description  : Returns Missile variable (for heirs)
 * Returns      : (object) Missile
 */
object
query_missile()
{
    return Missile;
}

/*
 * Function     : set_missile()
 * Description  : Sets the Missile object (for heirs)
 * Returns      : (object) Missile
 */
void
set_missile(object new_missile)
{
    Missile = new_missile;
}

/*
 * Function     : query_thrower()
 * Description  : Returns Thrower variable (for heirs)
 * Returns      : (object) Missile
 */
object
query_thrower()
{
    return Thrower;
}

/*
 * Function     : set_missile()
 * Description  : Sets the Missile object (for heirs)
 * Returns      : (object) Missile
 */
void
set_thrower(object new_thrower)
{
    Thrower = new_thrower;
}

/*
 * Function     : query_target()
 * Description  : Returns Target variable (for heirs)
 * Returns      : (object) Missile
 */
object
query_target()
{
    return Thrower;
}

/*
 * Function     : set_missile()
 * Description  : Sets the Missile object (for heirs)
 * Returns      : (object) Missile
 */
void
set_target(object new_target)
{
    Thrower = new_target;
}

/*
 * Function     : query_throwing()
 * Description  : Returns Throwing variable (for heirs)
 * Returns      : (int) Throwing
 */
int
query_throwing()
{
    return Throwing;
}

/*
 * Function     : set_throwing()
 * Description  : Sets the Throwing variable (for heirs)
 * Arguments    : (int) new Throwing value
 */
void
set_throwing(int new_throwing_state)
{
    Throwing = new_throwing_state;
}

/* Returnable implementations: rope dart (javelin-like, 4 m), meteor hammer
(club), chain whip, bolas; non-returnable: knives (45 m) / darts (150 m),
axes, clubs, spears/plumbata (a javelin master could send this 70 m, with poor
individual accuracy vs. longbow's 300, so 1 room) (hurled rather like an axe
and called a javelin, so all sharp thrown things should check SS_WEP_JAVELIN to
determine ability to go far, hit accurately, and pierce). Special: net. D&D
range increments: javelin 30 ft, net 10, short spear 20, dagger 10, dart 20. */
