/*
 * gauntlet.c
 *
 * This object is the "King's Hand" required to shatter the chain
 * that binds Firestorm into place, to complete the calian sup.
 * guru quest.
 *
 * Players can only use it _once_, but can try to crush armours and
 * weapons with it as well, making it a nice present for another 
 * player after the quest is done *grin*.
 *
 * The object is only obtainable if someone is actually doing the
 * sup. guru quest (it's not loaded, otherwise), and must also
 * be charged by Raspatoon in Gelan with vampiric moss that players
 * must also bring to him (which only grows in one room in the
 * entire mud, which happens to be a death trap if you aren't
 * paying attention).
 *
 * Khail, Feb 8/97
 */ 
#pragma strict_types

#include "defs.h"
#include "../guru_quest.h"

#define AC 20

inherit "/std/armour";

int wear_alarm,
    charged;
string *have_used;

public int do_crush(string str);

/*
 * Function name: create_armour
 * Description  : Turns this object into actual armour.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_armour()
{
    set_name("gauntlet");
    add_name("armour");
    add_name(C_GURU_GAUNTLET_NAME);
    set_adj("polished");
    add_adj("silver");
    set_short("polished silver gauntlet"); 
    set_pshort("polished silver gauntlets"); 
    set_long("The gauntlet is fairly simple in appearance, " +
        "basically a large glove made for the right hand " +
        "out of silver.\n");
    set_ac(AC);
    set_am(({-2, 5, -3}));
    set_at(A_R_HAND);
    set_af(TO);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_M_NO_SELL, 1);
    have_used = ({});
}

/*
 * Function name: query_have_used
 * Description  : Returns an array of the players who have
 *                used the gauntlet.
 * Arguments    : n/a
 * Returns      : An array of real names of the players who
 *                have used the gauntlet.
 */
public string
*query_have_used()
{
    return have_used + ({});
}

/*
 * Function name: set_charged
 * Description  : Called by Raspatoon to activate the gauntlet when
 *                he finishes recharging it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
set_charged()
{
    charged = 1;
}

/*
 * Function name: query_charged
 * Description  : Returns the charged status of the gauntlet.
 * Arguments    : n/a
 * Returns      : 0 - Not charged.
 *                1 - Charged.
 */
public int
query_charged()
{
    return charged;
}

/*
 * Function name: feel_charge
 * Description  : Delivers a message to players wearing the
 *                gauntlet if it's charged.
 * Arguments    : who - Object pointer to the living wearing
 *                      the gauntlet.
 * Returns      : n/a
 */
public void
feel_charge(object who)
{
    tell_object(who, "As you pull on the gauntlet, you feel " +
        "a surge of power from it.\n");
}

/*
 * Fucntion name: remove (MASK)
 * Description  : Does some custom stuff when players are trying
 *                to remove the gauntlet. Here it removes the alarm
 *                to 'feel_surge' called by alarm when wearing it.
 * Arguments    : obj - Object pointer to the object to attempt and
 *                      remove.
 * Returns      : mixed - One of several failure/success outcomes,
 *                        see the sman page for details.
 */
public mixed
remove(object obj)
{
    if (!obj || obj != TO)
        return 0;

    else
        if (get_alarm(wear_alarm))
            remove_alarm(wear_alarm);
    return 0;
}

/*
 * Function name: wear (MASK)
 * Description  : Things to do when the gauntlet is worn. Here it
 *                simple sets a 0.5 second alarm to a message that's
 *                delivered if the gauntlet is charged.
 * Arguments    : obj - Object pointer to the object to wear.
 * Returns      : mixed - Varying success/fail as per the sman page.
 */
public mixed
wear(object obj)
{
    if (!obj || obj != TO)
        return 0;
    if (charged)
        wear_alarm = set_alarm(0.5, 0.0, &feel_charge(TP));
    return 0;
}

/*
 * Function name: init (MASK)
 * Description  : Called when the objects 'meet' each other. Here
 *                it's used to add the 'crush', 'smash' and 'break'
 *                commands.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    add_action(do_crush, "crush");
    add_action(do_crush, "smash");
    add_action(do_crush, "break");
}

/*
 * Function name: do_crush
 * Description  : Allows players to attempt to crush objects with
 *                the gauntlet. For success, the gauntlet must be
 *                charged, must be worn, and can only be used once
 *                by any player (though it can still be used, but
 *                only by other players). Players can attempt to
 *                crush 3 things. Weapons, armour, and the chain
 *                used to imprison Firestorm.
 * Arguments    : str - Arguments player provided to the verb.
 * Returns      : 0 - Nothing happend, keep threading.
 *                1 - Something happened, stop threading.
 */
public int
do_crush(string str)
{
    string verb;
    object target;

    verb = query_verb();

    NF(capitalize(verb) + " what?\n");

  /* Do nothing if the player failed to provide an argument. */
    if (!str || !strlen(str))
    {
        return 0;
    }

  /* Do nothing if the gauntlet isn't worn by the player */
  /* trying to crush something. */
    if (!query_worn() || query_worn() != TP)
    {
        NF("You must be wearing the gauntlet to " + verb +
            " anything.\n");
        return 0;
    }

  /* Player can only use it once. */
    if (member_array(TP->query_real_name(), have_used) >= 0)
    {
        write("The gauntlet will no longer grant you " +
            "it's power.\n");
        return 1;
    }
    
  /* Fail if they tried to crush something that isn't in */
  /* the player's inventory or environment. */
    if (!(target = present(str, environment(TP))))
    {
        if (!(target = present(str, TP)))
            return 0;
    }

  /* What to do if the target is a weapon. */
    if (target->check_weapon())
    {
        write("Using the King's Hand, you try to crush the " +
            target->short() + ".\n");
        say(QCTNAME(TP) + " attempts to crush " +
            LANG_ADDART(target->short()) + " with " +
            TP->query_possessive() + " gauntlet.\n");
        target->set_dull(target->query_dull() + 5);
        have_used += ({TP->query_real_name()});
        return 1;
    }

  /* What to do if the target is armour. */
    if (target->check_armour())
    {
        write("Using the King's Hand, you try to crush the " +
            target->short() + ".\n");
        say(QCTNAME(TP) + " tries to crush " +
            LANG_ADDART(target->short()) + " with " +
            TP->query_possessive() + " gauntlet.\n");
        target->set_condition(target->query_condition() + 5);
        have_used += ({TP->query_real_name()});
        return 1;
    }

  /* What to do if the target is the chain holding Firestorm. */
    if (target->id(C_GURU_CHAIN_NAME))
    {
        write("Using the King's Hand, you try to crush " +
            "the chain.\n");
        say(QCTNAME(TP) + " tries to crush the chain with " +
            TP->query_possessive() + " gauntlet.\n");
        target->try_break(TP);
        have_used += ({TP->query_real_name()});
        return 1;
    }

    NF("The gauntlet's powers don't seem to be able of " +
        "crushing that.\n");
    return 0;
}

