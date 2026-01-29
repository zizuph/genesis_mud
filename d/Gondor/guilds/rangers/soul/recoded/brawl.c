/*
 * /d/Gondor/guilds/rangers/soul/recoded/brawl.c
 *
 * This is the code that is needed to brawl an opponent. A brawl can either
 * disarm him or blind him for some time. If you are a Ranger of Ithilien, it
 * may knee him. If you are a Ranger of the North it may trip him. Currently, 
 * you are not certain what will happen if you brawl someone. Although there
 * is a slightly better chance that you will get the type of brawl you wanted, 
 * there is a random chance that you do any of the actions you are allowed. 
 * This code is prepared for an easy split though.
 *
 ****************************************************************************
 *
 * Brawl was originally coded by Elessar Telcontar, 1992.
 *
 * Recoded to the new Genesis ability system by Petros, May 2020
 */

#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/std/combat/combat.h"
#include DEBUGGER_LIB

/* Gondorian defs */
#include "/d/Gondor/defs.h"

/* Ranger guild definitions */
#include "../../rangers_new.h"

/* Local brawl definitions */
#include "brawl.h"

/* Prototypes */
public int          brawl(string str);
private int         check_choose(object player);
private int         access_brawl(string str);
public object       find_victim_to_brawl(object brawler, string str);
public int          still_has_to_recover(object brawler);
public int          can_attack(object brawler, object victim);
public int          can_hide_brawl(object brawler, object victim);
private int         can_avoid_brawl(object brawler, object victim);

public void         do_brawl(object brawler, object victim, int seen = 0);
public object       find_next_target(object brawler);
private void        decide_on_brawl_type(object brawler, object victim);
private void        blind_or_disarm(object brawler, object victim, int brawl,
                                    int wielding);
private void        do_blind(object victim, int seen = 0);
private void        do_disarm(object victim, int seen = 0);
private void        do_knee(object victim, int seen = 0);
private void        do_trip(object victim, int seen = 0);

public int          size_diff(object brawler, object victim);
private int         check_wielding(object pl);
private varargs int check_tohit(object brawler, object victim,
                                int type = BRAWL_BLIND);
private nomask int  fixnorm(int offence, int defence);
private int         check_seen_brawl(object brawler, object victim);

public int          stop_brawl(string str);
public void         reset_brawl_properties(object brawler, int all = 1);
public void         can_brawl_again(object brawler);

static void         brawl_bug(object brawler, string str);
#ifdef BRAWLDEBUG
public string query_brawl_stats(int fail = 0); 
public void remove_object();
#endif

/*
 * Function name: brawl
 * Description  : The actual command. This function is called when the
 *                player types brawl/blind/disarm/rknee/rtrip. What
 *                the player actually does (blind or disarm) is decided
 *                later if they have failed check_choose.
 * Arguments    : string str - the target as entered by the player
 * Returns      : 1/0
 */
public int
brawl(string str)
{
    int brawl = BRAWL_UNKNOWN;

    /* Ranger is allowed to choose their brawl type. */
    if (check_choose(this_player()))
    {
        switch(query_verb())
        {
        case "brawl":
            break;

        case "blind":
            brawl = BRAWL_BLIND;
            break;

        case "disarm":
            brawl = BRAWL_DISARM;
            break;

        case "rknee":
            if (this_player()->query_company() != "ithilien")
                return 0;

            brawl = BRAWL_KNEE;
            break;

        case "rtrip":
        case "trip":
            if (this_player()->query_company() != "north")
                return 0;

            brawl = BRAWL_TRIP;
            break;

        default:
            break;
        }
    }
    else
    {
        if (this_player()->query_company() != "north" &&
          (query_verb() == "rtrip" || query_verb() == "trip"))
            return 0;
        if (this_player()->query_company() != "ithilien" &&
          query_verb() == "rknee")
            return 0;
    }

    this_player()->add_prop(RANGER_I_BRAWL_TYPE, brawl);
    return access_brawl(str);
}

/*
 * Function name: check_choose
 * Description:   With guru brawl skill, a player may improve the
 *                chance that the chosen kind of brawl will be
 *                executed.
 * Argument:      object player - player object
 * Returns:       1/0 - success/failure
 */
private int
check_choose(object player)
{
    int skill;

    skill = (player->query_skill(SS_BRAWLING) - BRAWL_CHOOSE_MIN);
    if (skill <= 0)
        return 0;

    return (random(100) < (skill * BRAWL_CHOOSE_CHANCE /
      (100 - BRAWL_CHOOSE_MIN)));
}

/*
 * Function name: access_brawl
 * Description  : The actual brawl command.
 *                This function is called when the player types to
 *                brawl someone.
 * Arguments    : str - command line argument
 * Returns      : 1/0 - success/failure of the command
 */
private int
access_brawl(string str)
{
    object tp = this_player();
    object victim;
    int    recover,
           al_id,
           seen = 0;

    victim = find_victim_to_brawl(tp, str);
    if (!objectp(victim))
        return 0;

    if (!can_attack(tp, victim))
        return 1;

    if (tp->query_skill(SS_PUNISHMENT) == NO_BRAWL)
    {
        notify_fail("For some strange reason, you cannot seem to do that.\n");
        return 0;
    }

    tp->add_prop(RANGER_I_PREPARE_BRAWL, PREPARE_BRAWL);
    tp->add_prop(RANGER_I_TIME_BRAWL, time());
    tp->add_prop(RANGER_O_START_BRAWL, environment(tp));

    if (can_hide_brawl(tp, victim))
    {
        write("You prepare to brawl " + victim->query_the_name(tp) + ".\n");
    }
    else
    {
        if (can_avoid_brawl(tp, victim))
        {
            write("You prepare to brawl " + victim->query_the_name(tp) +
                ", though " + victim->query_pronoun() + " discovers " +
                "what you are planning to do and deftly avoids your " +
                "brawling maneuver! You have no idea what went wrong.\n");
            victim->catch_tell("With a shock, you discover that " +
                tp->query_the_name(victim) + " is preparing to brawl " +
                "you. Skillfully, you avoid " + tp->query_possessive() +
                " attempt, leaving " + tp->query_objective() +
                " dazed and confused.\n");

            tp->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
            recover = TIME_AFTER_BRAWL_FUMBLE(tp);
            tp->add_prop(RANGER_I_TIME_RECOVER, recover);
            al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(tp));
            tp->add_prop(RANGER_CBA_AID, al_id);
            return 1;
        }
        else
        {
            write("You prepare to brawl " + victim->query_the_name(tp) +
                ", though " + victim->query_pronoun() + " discovers " +
                "what you are planning to do and tries to avoid your " +
                "brawling maneuver.\n");
            victim->catch_tell("With a shock, you discover that " +
                tp->query_the_name(victim) + " is preparing to " +
                "brawl you. You try to avoid " + tp->query_possessive() +
                " attempt.\n");
            seen = 1;
        }

    }

    /* If player is suffering a short attack delay, we allow brawl to be */
    /* initiated with the delay added to the total prep time. */
    al_id = set_alarm(itof(TIME_BEFORE_ACTUAL_BRAWL +
        tp->query_prop(LIVE_I_ATTACK_DELAY)), 0.0,
        &do_brawl(tp, victim, seen));
    tp->add_prop(RANGER_DB_AID, al_id);
    return 1;
}

/*
 * Function name: find_victim_to_brawl
 * Description  : This function is called for general access. If first
 *                test whether the player is able to brawl and if so, it
 *                searches for an opponent. If this function fails,
 *                notify_fail will be set.
 * Arguments    : brawler - the player that wants to brawl
 *                str     - the command line string
 * Returns      : object  - the victim to brawl
 *                0       - no victim could be found
 */
object
find_victim_to_brawl(object brawler, string str)
{
    object  victim,
           *oblist;

    if (still_has_to_recover(brawler))
    {
        /* Notify_fail will be set in the function. */
        return 0;
    }

    if (brawler->query_ghost())
    {
        notify_fail("A ghost needs a body before it can brawl.\n");
        return 0;
    }

    if (!strlen(str))
    {
        if (!objectp(victim = (object)brawler->query_attack()))
        {
            notify_fail(capitalize(query_verb()) + " who?\n");
            return 0;
        }
    }
    else
    {
        oblist = PARSE_THIS(str, "[the] %l");
        if (sizeof(oblist) >= 2)
        {
            notify_fail("Be specific, you can't brawl " +
                COMPOSITE_LIVE(oblist) + " at the same time.\n");
            return 0;
        }
        else if (sizeof(oblist) == 1)
        {
            victim = oblist[0];
            if ((brawler->query_attack() != victim ||
              victim->query_attack() != brawler) &&
              (!CAN_SEE_IN_ROOM(brawler) || !CAN_SEE(brawler, victim)))
            {
                notify_fail("You cannot see or find anyone like that " +
                    "here to brawl.\n");
                return 0;
            }
        }
        else
        {
            notify_fail(capitalize(query_verb()) + " who?\n");
            return 0;
        }
    }

    return victim;
}

/*
 * Function name: still_has_to_recover
 * Description  : This function checks whether the player still has to
 *                recover from a brawl. If the brawl is 'stuck' for some
 *                reason the brawl will be reset. If the player can not
 *                brawl again, notify_fail will set to the appropriate
 *                message. This function may have some overhead, but that
 *                is meant to guard against all brawl bugs. If any problem
 *                is found, this function resets the brawl posibilities of
 *                the player completely without trying to partially reset
 *                them to let the player wait... If we make a mistake, he
 *                may have the pleasure of a quick recovery.
 * Arguments    : brawler - the player that wants to brawl
 * Returns      : 1 - the player still has to recover
 *                0 - the player can brawl again
 */
public int
still_has_to_recover(object brawler)
{
    int prep, rtime, start;

    prep  = (int)brawler->query_prop(RANGER_I_PREPARE_BRAWL);
    if (!prep)
    {
        reset_brawl_properties(brawler, 0);
        return 0;
    }

    start = (int)brawler->query_prop(RANGER_I_TIME_BRAWL);
    if (prep == PREPARE_BRAWL)
    {
        if ((time()) > (start + TIME_BEFORE_ACTUAL_BRAWL +
            TIME_TO_PROTECT_ERRORS))
        {
            reset_brawl_properties(brawler);
            return 0;
        }

        notify_fail("You were already preparing a brawl.\n\n");
        return 1;
    }

    if (prep != RECOVER_BRAWL && prep != MOVED_WHILE_BRAWLING)
    {
        reset_brawl_properties(brawler);
        return 0;
    }

    rtime = (int)brawler->query_prop(RANGER_I_TIME_RECOVER);
    if ((rtime < MIN_TIME_TO_RECOVER) || (rtime > MAX_TIME_TO_RECOVER))
    {
        reset_brawl_properties(brawler);
        return 0;
    }

    if (time() > (start + rtime + TIME_BEFORE_ACTUAL_BRAWL +
        TIME_TO_PROTECT_ERRORS))
    {
        reset_brawl_properties(brawler);
        return 0;
    }

    notify_fail(one_of_list(({
      "You are still somewhat out of balance from your last brawl.\n",
      "You do not feel ready to attempt another brawl yet.\n",})));

    return 1;
}

/*
 * Function name: can_attack
 * Description  : This function determines whether a certain person can and
 *                is allowed to attack someone else. If not, a fail message
 *                is written to the player.
 * Arguments    : brawler - the player who wants to brawl.
 *                victim  - the victim of the brawl.
 * Returns      : 1 - the brawl is possible/ allowed.
 *                0 - it is not possible to brawl.
 */
int
can_attack(object brawler, object victim)
{
    string  tmp;
    int     roomtp;
    mixed   nobrawl;

    set_this_player(brawler);

    if (!objectp(brawler))
        return 0;

    roomtp = environment(brawler)->query_prop(ROOM_I_TYPE);
    if ((roomtp == ROOM_UNDER_WATER) || (roomtp == ROOM_IN_WATER))
    {
        write("Brawling is quite impossible in this aquatic environment!\n");
        return 0;
    }

    tmp = environment(brawler)->query_prop(ROOM_M_NO_ATTACK);
    if (!objectp(brawler->query_attack()) && tmp)
    {
        if (stringp(tmp))
            brawler->catch_msg(tmp);
        else
            write("The peaceful surroundings calm your aggressive mind.\n");

        return 0;
    }

    tmp = victim->query_prop(OBJ_M_NO_ATTACK);
    if (tmp)
    {
        if (stringp(tmp))
            brawler->catch_msg(tmp);
        else
            write("You feel a strong force protecting that being.\n");

        return 0;
    }

    if ((!F_DARE_ATTACK(brawler, victim)) &&
        (member_array(victim, (object *)brawler->query_enemy(-1)) == -1))
    {
        write("Umm... no, You do not have enough self-discipline to dare!\n");
        return 0;
    }

    if (brawler->query_prop(LIVE_I_STUNNED))
    {
        write("You are stunned and cannot brawl right now!\n");
        return 0;
    }

    if (brawler->query_prop(LIVE_I_ATTACK_DELAY) > TIME_TO_PROTECT_ERRORS)
    {
        /* If delay is long, don't allow brawl.
         * If it is a delay shorter than TIME_TO_PROTECT_ERRORS,
         * allow the brawl but delay is added to preparation time.
         */
        write("You can't seem to compose yourself enough to brawl " +
            "right now.\n");
        return 0;
    }

    nobrawl = victim->query_prop(RANGER_M_NOT_BRAWL);
    if (stringp(nobrawl))
    {
        brawler->catch_msg(nobrawl);
        return 0;
    }
    else if (nobrawl || (victim->query_prop(RANGER_I_NOT_BRAWL)))
    {
        write("Your brawling seems pointless against this opponent.\n");
        return 0;
    }

    if (brawler->query_met(victim) &&
      (member_array(victim, brawler->query_enemy(-1)) == -1) &&
      (brawler->query_prop(LIVE_O_LAST_KILL) != victim))
    {
        write("Brawl " + victim->query_the_name(brawler) + "? It just " +
            "might make " + victim->query_objective() + " upset enough " +
            "that there will be a fight! Please confirm by trying again!\n");
        brawler->add_prop(LIVE_O_LAST_KILL, victim);
        return 0;
    }

    return 1;
}

/*
 * Function name: can_hide_brawl
 * Description  : This function will determine whether a player is able to
 *                discover that someone is preparing a brawl against him.
 *                He will learn every time he fails to notices that a
 *                brawl is prepared against him.
 *                This check is done at preparation time and
 *                determines the chance for avoiding the brawl as well
 *                as the chance of brawl to initiate combat.
 * Arguments    : brawler - the player that wants to brawl
 *                victim  - the player that is the intended victim
 * Returns      : 1 - it is possible to hide the action from him.
 *                0 - it is not possible to hide it from him.
 */
int
can_hide_brawl(object brawler, object victim)
{
    int recognize, awareness;

    if (!CAN_SEE_IN_ROOM(victim) || !CAN_SEE(victim, brawler))
        return 1;

    recognize = victim->query_prop(RANGER_I_RECOGNIZE_BRAWL);
    awareness = victim->query_skill(SS_AWARENESS);

    /* victim learns only if the brawl is successfully hidden: */
    if ((recognize + awareness) < (brawler->query_prop(OBJ_I_HIDE) +
      brawler->query_skill(SS_SNEAK) + brawler->query_skill(SS_BRAWLING)))

    {
        if (random(recognize) >= awareness)
            return 1;

        victim->add_prop(RANGER_I_RECOGNIZE_BRAWL,
            recognize + (awareness * BRAWL_RECOGNIZE_RATE / 100));

        return 1;
    }

    return 0;
}

/*
 * Function name: can_avoid_brawl
 * Description  : Compute whether the victim is able to avoid being brawled
 *                by the brawler. This function comes in the place of the
 *                former try_react_brawl and try_avoid_brawl for it is my
 *                opinion that you shall always try to avoid a brawl if you
 *                see that someone tries to brawl them. Let us hope that this
 *                function always returns 0 *grin*
 * Arguments    : brawler - the player that wants to brawl
 *                victim  - the intended victim
 * Returns      : 1 - the brawl can be avoided
 *                0 - the brawl cannot be avoided.
 */
private int
can_avoid_brawl(object brawler, object victim)
{
    if (!CAN_SEE(victim, brawler))
    {
        return 0;
    }
    else if (!CAN_SEE_IN_ROOM(victim) &&
      (random(100) > victim->query_skill(SS_BLIND_COMBAT)))
    {
        return 0;
    }
    else if (victim->resolve_task(TASK_DIFFICULT,
      ({ SKILL_AVG, TS_DEX, TS_INT, SKILL_END,
      SKILL_AVG, SS_AWARENESS, SS_DEFENCE, SKILL_END }), brawler,
      ({ TS_INT, brawler->query_skill(SS_BRAWLING) })) > 0)
    {
        return 1;
    }

    return 0;
}

/*
 * Function name: do_brawl
 * Description  : Checks several things to ensure that everything
 *                is still valid before the brawl hits as well as
 *                determining which effect a generic "brawl" command
 *                will have (blind/disarm/knee/trip). If the brawl is
 *                still valid, it calls the appropriate subfunction,
 *                do_blind, do_disarm, do_knee, do_trip to carry out
 *                the effects.
 * Arguments    : brawler - the brawler
 *                victim  - the victim of the brawl
 */
public void
do_brawl(object brawler, object victim, int seen = 0)
{
    int recover, al_id, type;

    set_this_player(brawler);

    if (!objectp(brawler))
        return;

    /* The player brawled, left and came back in before the brawl hit. */
    if ((brawler->query_prop(RANGER_I_PREPARE_BRAWL) == MOVED_WHILE_BRAWLING)
      && (environment(brawler) == brawler->query_prop(RANGER_O_START_BRAWL)))
    {
        write("You cancel the prepared brawl since you moved too much " +
            "while preparing.\n");
        brawler->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
        recover = TIME_AFTER_BRAWL_FUMBLE(brawler) / 4;
        brawler->add_prop(RANGER_I_TIME_RECOVER, recover);
        al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(brawler));
        brawler->add_prop(RANGER_CBA_AID, al_id);
        brawler->remove_prop(RANGER_O_START_BRAWL);
        return;
    }

    /* The player obviously decided to stop the brawl. */
    if (brawler->query_prop(RANGER_I_PREPARE_BRAWL) != PREPARE_BRAWL)
        return;

    /* The victim is gone. See if there's another one. */
    if ((!objectp(victim)) || (environment(brawler) != environment(victim)))
    {
        victim = find_next_target(brawler);
        /* No more opponents. */
        if (!objectp(victim))
        {
            write("You stop preparing your brawl since the intended target " +
                "is no longer present.\n");
            can_brawl_again(brawler);
            return;
        }

        write("Since your intended target is no longer present, you turn " +
            "your attention to " + victim->query_the_name(brawler) + ".\n");
    }

    if (brawler->query_prop(RANGER_I_BRAWL_TYPE) == BRAWL_UNKNOWN)
        decide_on_brawl_type(brawler, victim);

    brawler->add_prop(RANGER_I_PREPARE_BRAWL, RECOVER_BRAWL);
    recover = TIME_TO_BRAWL_AGAIN(brawler);

    brawler->add_prop(RANGER_I_TIME_RECOVER, recover);
    al_id = set_alarm(itof(recover), 0.0, &can_brawl_again(brawler));
    brawler->add_prop(RANGER_CBA_AID, al_id);
    brawler->add_prop(LIVE_O_LAST_KILL, victim);

    type = brawler->query_prop(RANGER_I_BRAWL_TYPE);
    if (brawler->query_prop(LIVE_I_STUNNED))
    {
        write("You are stunned and cannot brawl right now!\n");
        return;
    }

    /* Do we hit the enemy? rknee is checked in do_knee. */
    if ((type != BRAWL_KNEE) && (check_tohit(brawler, victim, type) < 0))
    {
        write("Your attempt to brawl " +
                victim->query_the_name(brawler) + " fails miserably, " +
                "and you stumble to regain your balance.\n");

        if (seen)
        {
            victim->catch_tell(brawler->query_The_name(victim) +
                " tries to brawl you, " + "but fails, losing " +
                brawler->query_possessive() + " balance for a while.\n");
            brawler->tell_watcher(QCTNAME(brawler)+" tries to brawl " +
                QTNAME(victim) + ", but fails, losing " +
                brawler->query_possessive() + " balance for a moment.\n",
                victim, brawler);

            if (!objectp(victim->query_attack()))
            {
                victim->add_prop(LIVE_O_LAST_KILL, brawler);
                victim->attack_object(brawler);
            }
        }

        return;
    }

    switch (type)
    {
    case BRAWL_DISARM:
        do_disarm(victim, seen);
        break;

    case BRAWL_TRIP:
        do_trip(victim, seen);
        break;

    case BRAWL_KNEE:
        do_knee(victim, seen);
        break;

    case BRAWL_BLIND:
    default:
        do_blind(victim, seen);
        break;
    }
}

/*
 * Function name: find_next_target
 * Description  : Finds the next target if the first one is gone.
 * Arguments    : object brawler - the brawler
 * Returns      : The new target
 */
public object
find_next_target(object brawler)
{
    int i, size;
    object* victims;

    victims = brawler->query_enemy(-1);
    for (i = 0, size = sizeof(victims); i < size; i++)
        if (objectp(victims[i]) && present(victims[i], environment(brawler)))
            return victims[i];

    return 0;
}

/*
 * Function name: decide_on_brawl_type
 * Description  : As long as the brawl command can still be used for blind,
 *                disarm, rknee and trip, this function is used to
 *                determine whether the player disarms, blinds, trips
 *                or knees. If the opponent does not have a weapon, you
 *                will always try to blind him, if not it uses random
 *                to determine the type.
 * Arguments    : brawler - the player that wants to brawl
 *                victim  - the intended victim
 */
private void
decide_on_brawl_type(object brawler, object victim)
{
    int sd, stat_diff,
        rndm = random(100),
        brawl = brawler->query_skill(SS_BRAWLING),
        wielding = check_wielding(victim);

    /* If a two handed weapon was disarmed, try disarm again: */
    if ((rndm < (brawl / 2)) && (wielding == 2))
    {
        brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_DISARM);
        return;
    }

    switch (brawler->query_company())
    {
    case "north":
        /* Compare strength of brawler with strength of victim. */
        stat_diff = fixnorm(brawler->query_skill(SS_STR),
                    victim->query_skill(SS_STR));

        if (((sd = size_diff(brawler, victim)) < 10) &&
          (rndm < (BRAWL_BASE_TRIP_RATE - stat_diff - sd)))
        {
            brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_TRIP);
        }
        else
        {
            blind_or_disarm(brawler, victim, brawl, wielding);
        }

        break;

    case "ithilien":
        if ((brawler->query_attack() == victim) &&
          (rndm >= (50 + victim->query_hp() * 50 / victim->query_max_hp())) &&
          (size_diff(brawler, victim) < 10))
        {
            brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_KNEE);
        }
        else
        {
            blind_or_disarm(brawler, victim, brawl, wielding);
        }

        break;

    default:
        blind_or_disarm(brawler, victim, brawl, wielding);
        break;
    }
}

/*
 * Function name: blind_or_disarm
 * Description:   Chance for disarm vs blind is 50 :  50,
 *                if no weapon is wielded        0 : 100,
 *                if victim is blinded up to    90 : 100
 *                depending on skill.
 * Arguments:     object brawler,
 *                object victim,
 *                int brawl - brawl skill
 *                int wielding - true if the victim is wielding a weapon
 */
private void
blind_or_disarm(object brawler, object victim, int brawl, int wielding)
{
    int rndm = random(100);

    if (!wielding)
    {
        brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_BLIND);
    }
    else if ((rndm < 50) ||
      ((brawl > 50) &&
      objectp(present("Ranger_Blind_Object", victim)) &&
      (rndm < (10 + brawl * 80 / 100))))
    {
#ifdef BRAWLDEBUG
        Brawl_Stats[22]++;
        Brawl_Stats[ brawl / 10 ]++;
#endif
        brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_DISARM);
    }
    else
    {
#ifdef BRAWLDEBUG
        Brawl_Stats[22]++;
        Brawl_Stats[ brawl/10 + 11]++;
#endif
        brawler->add_prop(RANGER_I_BRAWL_TYPE, BRAWL_BLIND);
    }

    BRAWLDEBUG_MSG(brawler->query_name() + " BD: " + brawl + ", " +
        wielding + ", " + ((brawler->query_prop(RANGER_I_BRAWL_TYPE) ==
        BRAWL_BLIND) ? "BLIND" : "DISARM"));
}

/*
 * Function name: do_blind
 * Description  : Gives appropriate messages for blinding and clones
 *                the blind object.
 * Arguments    : victim  - the victim of the brawl
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_blind(object victim, int seen = 0)
{
    object blind_object, brawler = this_player();
    int    already_blinded = 0,
           time_brawl, busy_hands;
    mixed  blind_prop;
    string how;

    blind_prop = victim->query_prop(RANGER_M_NOT_BLIND);
    if (stringp(blind_prop))
    {
        brawler->catch_msg(blind_prop);
        return;
    }
    else if (blind_prop || victim->query_prop(RANGER_I_NOT_BLIND))
    {
        write("It seems impossible to blind " +
            victim->query_the_name(brawler) + ".\n");
        return;
    }

    blind_object = present("Ranger_Blind_Object", victim);
    if (objectp(blind_object))
    {
        already_blinded = 1;
    }
    else
    {
        setuid();
        seteuid(getuid());

        blind_object = clone_object(BLIND_OBJECT);
    }

    if (brawler->query_weapon(W_BOTH))
        busy_hands = 1;
    else if (brawler->query_weapon(W_RIGHT) && brawler->query_weapon(W_LEFT))
        busy_hands = 1;

    if (busy_hands)
        how = "kick";
    else
        how = "throw";

    if (seen || check_seen_brawl(brawler, victim))
    {
        blind_object->set_brawler(brawler);
        victim->catch_tell(brawler->query_The_name(victim) + " suddenly " +
            how + "s a shower of sand into your eyes! You are blinded!\n");
    }
    else
    {
        victim->catch_tell("You scream loudly as a shower of sand hits " +
            "your eyes! You are blinded!\n");
    }

    brawler->reveal_me(1);

    if (already_blinded)
    {
        write("You successfully " + how + " some more sand in the eyes of " +
            victim->query_the_name(brawler) + ". " +
            capitalize(victim->query_pronoun()) + " is still blinded!\n");
        tell_room(environment(brawler), QCTNAME(brawler) + " manages " +
            "to " + how + " some more sand into the already blinded " +
            "eyes of " + QTNAME(victim) + "!\n", ({ brawler, victim }), );
    }
    else
    {
        write("You successfully " + how + " a shower " + "of sand into " +
            "the eyes of " + victim->query_the_name(brawler) + ". " +
            capitalize(victim->query_pronoun(brawler)) + " looks blinded!\n");

        if (busy_hands)
            how = " kicks at the dusty ground,";
        else
            how = " jerks " + brawler->query_possessive() + " hand up,";

        tell_room(environment(brawler), QCTNAME(brawler) + " suddenly" +
            how + " sending a shower of sand into the eyes of " +
            QTNAME(victim) + "!\n", ({ brawler, victim }), );
    }

    time_brawl = brawler->query_skill(SS_BRAWLING) / (2 + already_blinded * 2);

    if (time_brawl > MAX_TIME_BRAWL)
        time_brawl = MAX_TIME_BRAWL;

    if (time_brawl < MIN_TIME_BRAWL)
        time_brawl = MIN_TIME_BRAWL;

    blind_object->set_time(time_brawl);

    if (!already_blinded)
        blind_object->move(victim, 1);
}

/*
 * Function name: do_disarm
 * Description  : Gives appropriate messages for disarming and clones
 *                the disarm object.
 * Arguments    : victim  - the victim of the brawl
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_disarm(object victim, int seen = 0)
{
    object disarm_object, brawler = this_player();
    int    time_brawl, attack_brawler, was_disarmed;
    mixed  nobrawl;

    nobrawl = victim->query_prop(RANGER_M_NOT_DISARM);
    
    if (stringp(nobrawl))
    {
        brawler->catch_msg(nobrawl);
        return;
    }
    else if ((intp(nobrawl) && (nobrawl != 0)) || ((victim->query_prop(RANGER_I_NOT_DISARM) != 0) && victim->query_npc()))
    {
        write("It seems impossible to disarm " +
            victim->query_the_name(brawler) + ".\n");
        return;
    }

    disarm_object = present("Ranger_Disarm_Object", victim);
    if (objectp(disarm_object))
    {
        if (disarm_object->query_two_handed())
            was_disarmed = 1;
    }

    if (!objectp(disarm_object) || !was_disarmed)
    {
        setuid();
        seteuid(getuid());

        disarm_object = clone_object(DISARM_OBJECT);
    }

    if (seen || check_seen_brawl(brawler, victim))
    {
        disarm_object->set_seen();
        victim->catch_tell(brawler->query_The_name(victim) + " delivers " +
            "a painful blow to your hand!\n");
    }
    else
    {
        victim->catch_tell("Something hits you painfully on your hand!\n");
    }

    brawler->reveal_me(1);

    write("You skillfully deliver a painful blow to " +
        victim->query_the_possessive_name(brawler) + " hand!\n");
    tell_room(environment(brawler), QCTNAME(brawler) + " delivers a " +
        "painful blow to " + QTPNAME(victim) + " hand!\n",
        ({ brawler, victim }) );
    disarm_object->set_brawler(brawler);
    time_brawl = brawler->query_skill(SS_BRAWLING) / 2;

    if (time_brawl > MAX_TIME_BRAWL)
        time_brawl = MAX_TIME_BRAWL;

    if (time_brawl < MIN_TIME_BRAWL)
        time_brawl = MIN_TIME_BRAWL;

    disarm_object->set_time(time_brawl);

    if (!was_disarmed)
    {
        disarm_object->move(victim, 1);
    }
    else
    {
        if (disarm_object->query_two_handed())
            disarm_object->complete_disarm();
    }

    if (attack_brawler)
    {
        if (!victim->query_attack())
        {
            write(victim->query_The_name(brawler) + " glares at you " +
                "angrily and attacks you!\n");
            brawler->attack_object(victim);
        }
        else
        {
            write(victim->query_The_name(brawler) + " throws you a " +
                "hateful glare, but continues " +
                victim->query_possessive() + " fight.\n");
            victim->query_combat_object()->cb_add_enemy(brawler);
        }
    }
}

/*
 * Function name: do_knee
 * Description  : This function takes care of the Ithilien Company's
 *                kneeing effect. It uses a BLUDGEON attack at the
 *                lower abdomen (kidneys, groin) and will allow belts
 *                to subtract from the damage.
 * Arguments    : victim  - the living who stands to be brawled.
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_knee(object victim, int seen = 0)
{
    int    wchit, phurt, hp, dam, phit, wpen, ac, hum, sd, time_stun;
    object cobj, *wep, belt, stun_ob, brawler = this_player();
    string how, where, how2;

    /* For 'knee' we use the standard cb_tohit function to */
    /*  determine the chance of a hit: */
    cobj = brawler->query_combat_object();
    wep = brawler->query_weapon(-1);

    if (sizeof(wep))
            wchit = wep[0]->query_hit();
    else
            wchit = W_HAND_HIT;

    wchit += F_UNARMED_HIT(brawler->query_skill(SS_BRAWLING),
                 brawler->query_skill(SS_DEX));

    if (cobj->cb_tohit(-1, wchit, victim) < 0)
    {
        write("Your attempt to knee " + victim->query_the_name(brawler) +
            " fails miserably, and you stumble to regain your balance.\n");

        if (seen)
        {
            victim->catch_tell(brawler->query_The_name(victim) +
                " tries to knee you, but fails, losing " +
                brawler->query_possessive() + " balance for a while.\n");
            brawler->tell_watcher(QCTNAME(brawler) + " tries to knee " +
                QTNAME(victim) + ", but fails, losing " +
                brawler->query_possessive() + " balance for a moment.\n",
                victim, brawler);

            if (!objectp(victim->query_attack()))
            {
                victim->add_prop(LIVE_O_LAST_KILL, brawler);
                victim->attack_object(brawler);
            }
        }

        return;
    }

    if (victim->query_ghost())
    {
        write(victim->query_The_name(brawler) + " is already dead.\n");
        return;
    }

    if (seen || check_seen_brawl(brawler, victim))
    {
        seen = 1;
    }

    setuid();
    seteuid(getuid());

    sd = size_diff(brawler, victim);
    if (sd > 10)
    {
        write(victim->query_The_name(brawler) + " is just too big for " +
            "you to try to knee.\n");
        return;
    }

    brawler->reveal_me(1);

    belt = victim->query_armour(A_WAIST);
    if (objectp(belt))
        ac = belt->query_ac() + belt->query_am()[2];

    phit = random(F_PENMOD(brawler->query_stat(SS_STR) / 4,
        brawler->query_skill(SS_BRAWLING) / 2 + 25 * (1 - seen)));
    ac = random(ac);
    dam = F_DAMAGE(phit, ac);

    if (dam < 1)
        dam = 0;

    hp = victim->query_hp();

    if (victim->query_wiz_level() && (dam >= hp))
    {
        victim->catch_tell(brawler->query_The_name(victim) +
            " knees you in the groin.\n");
        victim->catch_tell("Your wizardhood protects you from death.\n");
        tell_room(environment(victim), QCTNAME(victim) +
            " is immortal and fails to die!\n", victim);
        return;
    }

    if ((dam > 0) && hp)
    {
        phurt = (100 * dam) / hp;

        if (phurt > 100)
            phurt = 100;

        if (dam && !phurt)
            phurt = 1;
    }
    else if (dam > 0)
    {
        phurt = 100;
    }
    else
    {
        phurt = -1;
    }

    if (dam > 0)
        victim->heal_hp(-dam);

    if (!objectp(victim->query_attack()))
        brawler->attack_object(victim);
    else
        victim->query_combat_object()->cb_add_enemy(brawler);

    if (phurt >= 0)
        victim->add_panic(2 + phurt / 5);

    if (dam > (random(victim->query_stat(SS_DIS)) / 2))
        victim->cmdhooks_break_spell();

    if (phurt == -1)
    {
        write("Your attempt to knee " + victim->query_the_name(brawler) +
            " fails miserably, " + "and you stumble to regain balance.\n");
        brawler->add_attack_delay(random(4) + 1, 1);
        brawler->add_fatigue(-3);

        /* The victim only knows the brawler fails, if he knows the */
        /* brawler tried. */
        if (seen)
        {
            victim->catch_tell(brawler->query_The_name(victim) +
                " tries to knee you, but fails, losing " +
            brawler->query_possessive() + " balance for a while.\n");
            brawler->tell_watcher(QCTNAME(brawler) + " tries to knee " +
                QTNAME(victim) + ", but fails, losing " +
            brawler->query_possessive() + " balance for a moment.\n",
                victim, brawler);
        }

        return;
    }

    hum = victim->query_humanoid();

    switch (phurt)
    {
    case 0:
        how = "but it doesn't seem to do any harm";

        if (hum)
            where = "thigh";
        else
            where = "body";

        break;
    case 1..4:
        how = "but it causes only a little pain";

        if (hum)
            where = "hip";
        else
            where = "body";

        break;
    case 5..9:
        how = "and it seems to hurt a little";

        if (hum)
            where = "stomach";
        else
            where = "middle";

        break;
    case 10..19:
          how = "causing some pain";

          if (hum)
              where = "stomach";
          else
              where = "middle";

          break;
    case 20..34:
          how = "rather painfully";

          if (hum)
              where = "kidneys";
          else
              where = "torso";

          break;
    case 35..54:
          how = "and it really hurts bad";

          if (hum)
              where = "groin";
          else
              where = "torso";

          break;
    case 55..84:
          how = "inflicting severe pain";

          if (hum)
              where = "groin";
          else
              where = "softer parts";

          break;
    case 85..99:
          how = "causing severe internal damage";

          if (hum)
              where = "groin";
          else
              where = "softer parts";

          break;
    default:
          how = "with a devastating result";
          how2 = "and the pain is surely killing you";

          if (hum)
              where = "groin";
          else
              where = "softer parts";

          break;
    }

    if (!strlen(how2))
        how2 = how;

    write("You raise your knee, hitting " + victim->query_the_name(brawler) +
        " in the " + where + ", " + how + ".\n");

    if (!seen)
    {
        victim->catch_tell("Suddenly something hits you in " +
            where + ", " + how2 + ".\n");
    }
    else
    {
        victim->catch_tell(brawler->query_The_name(victim) +
            " suddenly raises a knee, hitting you in the " +
            where + ", " + how2 + ".\n");
    }

    brawler->tell_watcher(QCTNAME(brawler) + " suddenly raises a knee, " +
        "hitting " + victim->query_the_name(brawler) + " in the " +
        where + ", " + how + ".\n", victim, brawler);

    if (phurt > 6 || dam > 66)
    {
        time_stun = MAX(((brawler->query_skill(SS_BRAWLING) +
            brawler->query_ranger_rank()) / 10 - sd), MIN_TIME_BRAWL);


        stun_ob = present("Ranger_Stun_Object", victim);
        if (!objectp(stun_ob) &&
            !victim->query_prop(LIVE_I_NO_STUN))
        {
            setuid();
            seteuid(getuid());

            stun_ob = clone_object(RANGERS_OBJ + "stun_ob");
            stun_ob->set_brawler(brawler);
            stun_ob->set_time(time_stun);
            stun_ob->set_seen(seen);
            stun_ob->move(victim,1);
            victim->add_stun();
        }
        else
        {
            stun_ob->set_brawler(brawler);
            stun_ob->set_time(time_stun);
            stun_ob->set_seen(seen);
        }
    }

    if (victim->query_hp() <= 0)
        victim->do_die(brawler);

    return;
}

/*
 * Function name: do_trip
 * Description  : This function handles the stunning effect that
 *                Rangers of the North can deliver.
 * Arguments    : victim - the victim of the brawl
 *                seen    - victim already recognized the brawler at
 *                          prep time
 */
private void
do_trip(object victim, int seen = 0)
{
    int    time_stun,
           sd;
    string how,
           how2,
           how3;
    object stun_ob, brawler = this_player();
    mixed  nobrawl;

    nobrawl = victim->query_prop(RANGER_M_NOT_TRIP);
    if (stringp(nobrawl))
    {
        brawler->catch_msg(nobrawl);
        return;
    }
    else if ((intp(nobrawl) && (nobrawl != 0)) ||
      (victim->query_prop(RANGER_I_NOT_TRIP) != 0))
    {
        write("It seems impossible to trip " +
          victim->query_the_name(brawler) + ".\n");
        return;
    }

    if (victim->query_prop(LIVE_I_NO_STUN))
    {
        write(victim->query_The_name(brawler) + " isn't affected " +
            "by tripping.\n");
        return;
    }

    sd = size_diff(brawler, victim);
    if (sd > 10)
    {
        write(victim->query_The_name(brawler) + " is just too big for " +
            "you to try to trip.\n");
        return;
    }

    if (!seen && !check_seen_brawl(brawler, victim))
    {
        write("You sneak a foot between " +
            victim->query_the_possessive_name(brawler) + ", and stand " +
            "back to watch the unprepared " + victim->query_race_name() +
            " struggle to keep " + victim->query_possessive() + " balance!\n");
        victim->catch_tell("You trip over something, and struggle to " +
            "stay on your feet!\n");
        how = "who was quite unaware";
        how2 = "struggles to regain " + victim->query_possessive() +
            " balance";
    }
    else if ((brawler->query_skill(SS_BRAWLING) +
      brawler->query_stat(SS_STR)) < (victim->query_skill(SS_ACROBAT) +
      victim->query_stat(SS_DEX) + 10 * (sd - 1)))
    {
        victim->catch_tell(brawler->query_The_name(victim) + " tries " +
            "to trip you, but you manage to avoid it!\n");
        write("You try to trip " + victim->query_the_name(brawler) +
            " but " + victim->query_pronoun() + " manages to avoid it!\n");
        return;
    }
    else
    {
        seen = 1;
        switch (sd)
        {
        case 0..2:
            how = "without difficulty";
            how2 = "stumbles around, wavering while trying to regain balance";
            how3 = "stumble around, waving your arms, trying to regain balance";            break;
        case 3..5:
            how = "with some problems";
            how2 = "stumbles backwards, out of balance for a moment";
            how3 = "stumble backwards, out of balance for a moment";
            break;
        case 6..10:
            how = "with great luck";
            how2 = "takes a few steps back, to regain balance";
            how3 = "take a few steps back, regaining balance";
            break;
        }
    }

    brawler->reveal_me(1);

    if (seen)
    {
        write("You manage to trip " + victim->query_the_name(brawler) +
            " " + how + ". " + capitalize(victim->query_pronoun()) +
            " " + how2 + ".\n");
        victim->catch_tell(brawler->query_The_name(victim) +
            " skillfully trips you, and you " + how3 + ".\n");
    }

    brawler->tell_watcher(QCTNAME(brawler) + " manages to trip " +
        QTNAME(victim) + " " + how + ", and " + QTNAME(victim) + " " +
        how2 + ".\n", victim, brawler);
    time_stun = MAX(((brawler->query_skill(SS_BRAWLING) +
        brawler->query_ranger_rank()) / 10 - sd), MIN_TIME_BRAWL);

    stun_ob = present("Ranger_Stun_Object",victim);
    if (!objectp(stun_ob))
    {
        setuid();
        seteuid(getuid());

        stun_ob = clone_object(RANGERS_OBJ + "stun_ob");
        stun_ob->set_brawler(brawler);
        stun_ob->set_time(time_stun);
        stun_ob->set_seen(seen);
        stun_ob->move(victim,1);
        victim->add_stun();
    }
    else
    {
        stun_ob->set_brawler(brawler);
        stun_ob->set_time(time_stun);
        stun_ob->set_seen(seen);
    }
}


/*
 * Function name: size_diff
 * Description  : Tests the difference in volume and weight
 * Arguments    : brawler - the player who tries to brawl
 *                victim - the living being brawled
 * Returns      : The ratio between victim's and brawler's volume and
 *                weight
 */
int
size_diff(object brawler, object victim)
{
    return ((victim->query_prop(OBJ_I_VOLUME) /
        brawler->query_prop(OBJ_I_VOLUME)) +
        (victim->query_prop(OBJ_I_WEIGHT) /
        brawler->query_prop(OBJ_I_WEIGHT))) / 2;
}

/*
 * Function name: check_wielding
 * Description  : Tests if pl is wielding a weapon.
 * Arguments    : pl - the living we want to test.
 * Returns      : 0 - no weapon wielded.
 *                1 - some kind of weapon wielded.
 *                2 - successfully disarmed a two-handed weapon
 */
private int
check_wielding(object pl)
{
    object  ob;

    if (sizeof(pl->query_weapon(-1)))
    {
        return 1;
    }
    else if (objectp(ob = present("Ranger_Disarm_Object", pl)) &&
      ob->query_two_handed())
    {
        return 2;
    }

    return 0;
}

/*
 * Function name: check_tohit
 * Description:   All the checks from cb_tohit for the special attacks
 *                that do no hp damage.
 * Arguments:     object brawler - the ranger who is brawling
 *                object victim  - the victim
 *                int    type    - brawl type (RANGER_I_BRAWL_TYPE)
 * Returns:       > 0 if we hit, else < 0
 */
private varargs int
check_tohit(object brawler, object victim, int type = BRAWL_BLIND)
{
    int    weight, vic_vol, whit, old, tmp, bskill;
    object cobj = brawler->query_combat_object();

#ifdef BRAWLDEBUG
    Fail_Stats[22]++;
#endif

    /* Three factors are normalized (-50, 50) in the 'to-hit'.
     * 1 - brawl skill vs defence/parry skill
     * 2 - Weight
     * 3 - Volume
     * 4 - Dexterity
     * These are weighted with the factors (4, 1, 1, 2)
     */

    /* For brawl, we check the defence and parry skills, but with a
     * reduced effectiveness for parry.
     * This could be modified depending on the brawl type:
     * Only unarmed combat checked for blind and trip, parry check
     * fully for disarm.
     */
    tmp = victim->query_skill(SS_DEFENSE);

    /* Parry skill does not help to avoid throwing of sand. */
    if (type != BRAWL_BLIND)
    {
        /* Any weapons wielded? */
        if (sizeof((object *)victim->query_weapon(-1) - ({ 0 })))
            tmp += (int)victim->query_skill(SS_PARRY) / 2;
        else
            tmp += (int)victim->query_skill(SS_UNARM_COMBAT) / 2;
    }

    /* Is it dark or opponent invis? Then how well do we fight?
     *
     * The check for light levels and invisibility is contained in
     * find_victim_to_brawl(), making it impossible to brawl unless we
     * can see the victim.
     * We add the check for the opponent, however:
     */
    if (!CAN_SEE_IN_ROOM(victim) || !CAN_SEE(victim, brawler))
    {
        tmp = victim->query_skill(SS_BLIND_COMBAT) * tmp / 100;
    }

    bskill = brawler->query_skill(SS_BRAWLING) / 2;
    whit = 4 * fixnorm(random(bskill) + random(bskill) +
        random(bskill) + random(bskill), random(tmp));

    old = whit;
    weight = brawler->query_encumberance_weight();
    vic_vol = victim->query_encumberance_volume();
    whit += 2 * fixnorm(brawler->query_stat(SS_DEX),
        victim->query_stat(SS_DEX)) -
        fixnorm(brawler->query_prop(CONT_I_VOLUME),
        victim->query_prop(CONT_I_VOLUME)) -
        fixnorm(weight + vic_vol, weight + vic_vol);

    BRAWLDEBUG_MSG(brawler->query_name() + " HIT:" + whit + ", " + old);

#ifdef BRAWLDEBUG
    bskill /= 5;
#endif

    if (whit > 0)
    {
#ifdef BRAWLDEBUG
        Fail_Stats[bskill]++;
#endif
        return 1;
    }
    else
    {
#ifdef BRAWLDEBUG
        Fail_Stats[bskill + 11]++;
#endif
        return whit - 1;
    }
}

/*
 * Function name: fixnorm
 * Description:   Normalize offensive/defensive values taken from
 *                /std/combat/cbase where it is declared static.
 * Arguments:     int offense - offensive value
 *                int defense - defensive value
 * Returns:       Value in the range -50 .. 50
 */
private nomask int
fixnorm(int offence, int defence)
{
    if ((offence + defence) == 0)
        return 0;

    return ((100 * offence) / (offence + defence)) - 50;
}

/*
 * Function name: check_seen_brawl
 * Description:   check if the victim notices who has brawled him
 *                this is a check _after_ the brawl, used to determine
 *                if the brawl initiates combat
 */
private int
check_seen_brawl(object brawler, object victim)
{
    return (CAN_SEE_IN_ROOM(victim) && CAN_SEE(victim, brawler) &&
      (victim->resolve_task(TASK_SIMPLE, ({ TS_INT, SS_AWARENESS }),
        brawler, ({ &brawler->query_prop(OBJ_I_HIDE), SS_SNEAK })) > 0));
}

/*
 * Function name: stop_brawl
 * Description  : The command to stop a brawl in preparation.
 * Arguments    : str - as entered by the player, should be brawl
 * Returns      : 1/0
 */
public int
stop_brawl(string str)
{
    object tp;
    int prep;

    if ((str != "brawl") && (str != "brawling"))
    {
        notify_fail("Stop what? The world?\n");
        return 0;
    }

    tp = this_player();
    /* All possible errors are handled in this function. */
    if (!still_has_to_recover(tp))
    {
        write("You are able to brawl without any further preparation.\n");
        return 1;
    }

    prep = (int)tp->query_prop(RANGER_I_PREPARE_BRAWL);
    /* The Ranger can brawl again without further wait. */
    if (prep == PREPARE_BRAWL)
    {
        write("You decide to stop preparing for a brawl.\n");
        reset_brawl_properties(tp);
        return 1;
    }

    write("You have to recover from your last brawl.\n");
    return 1;
}

/*
 * Function name: reset_brawl_properties
 * Description  : Removes all brawl-related properties from a person.
 * Arguments    : brawler - the player that is brawling
 */
public void
reset_brawl_properties(object brawler, int all = 1)
{
    int al_id;

    brawler->remove_prop(RANGER_I_TIME_RECOVER);
    brawler->remove_prop(RANGER_I_TIME_BRAWL);
    brawler->remove_prop(RANGER_I_PREPARE_BRAWL);
    brawler->remove_prop(RANGER_O_START_BRAWL);

    if (all)
        brawler->remove_prop(RANGER_I_BRAWL_TYPE);

    al_id = (int)brawler->query_prop(RANGER_DB_AID);
    if (al_id)
    {
        remove_alarm(al_id);
        brawler->remove_prop(RANGER_DB_AID);
        al_id = 0;
    }

    al_id = (int)brawler->query_prop(RANGER_CBA_AID);
    if (al_id)
    {
        remove_alarm(al_id);
        brawler->remove_prop(RANGER_CBA_AID);
    }
}

/*
 * Function name: can_brawl_again
 * Description  : Called when the brawler has recovered from her
 *                last brawl and is able to brawl again.
 * Arguments    : brawler - the player that can brawl again.
 */
public void
can_brawl_again(object brawler)
{
    brawler->catch_tell("\nYou once again feel ready to try a brawl.\n\n");
    reset_brawl_properties(brawler);
}

/*
 * Function name: brawl_bug
 * Description  : Log a bug with the brawl command.
 *                Is this used anywhere?
 * Arguments    : brawler - the player that was brawling
 *                str     - the fail message.
 */
static void
brawl_bug(object brawler, string str)
{
    setuid();
    seteuid(getuid());

    log_file(BRAWL_BUG_LOG, (ctime(time()) + ", " +
        capitalize(brawler->query_real_name()) + ": " + str));
}

#ifdef BRAWLDEBUG
/*
 * Function name: query_brawl_stats
 * Description  : Used for debugging purposes.
 */
public string
query_brawl_stats(int fail = 0)
{
    int     i,
           *stats;
    string  msg;

    if (fail)
        stats = Fail_Stats;
    else
        stats = Brawl_Stats;
    msg = "Total number of entries: " + stats[22];
    if (fail)
        msg += "\n\tSkill\tSuccess\tFailure\n";
    else
        msg += "\n\tSkill\tDisarm\tBlind\n";
    for (i = 0; i <= 10; i++)
        msg += "\t" + i * 10 + "\t" + stats[i] + "\t" + stats[11 + i] + "\n";
    return msg;
}

/*
 * Function name: remove_object
 * Description  : Used for debugging purposes.
 */
public void
remove_object()
{
    setuid();
    seteuid(getuid());

    log_file("brawl_stats", "\n\t" + ctime(time()) + "\n" +
        query_brawl_stats() + query_brawl_stats(1));
    destruct();
}
#endif
