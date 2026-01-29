/*
 * macros.c
 *
 * This file contains (or will contain) various functions
 * that are used frequently enough to be referenced by
 * several pieces of code domain-wide, but are either
 * too small or unwieldy to be inherited in a lib module.
 * They are therefore placed here, and accessed through
 * macros defined in /d/Khalakhor/sys/macros.h
 *
 * Khail - June 21/97
 */

#include <stdproperties.h>
#include <formulas.h>

/*
 * Function name: can_attack
 * Description  : This function will return 0 if ob1
 *                can attack ob2. Otherwise, it will
 *                return a variety of numbers, each
 *                representing the reason of failure.
 *                It will also generate default failure
 *                messages, if the verbose toggle is
 *                activated. Note that here, verbose mode
 *                will only provide a string that contains
 *                the default failure message, it will
 *                not process the message and deliver it
 *                to the attacker.
 * Arguments    : ob1 - Object pointer to the attacker.
 *                ob2 - Object pointer to the target.
 *                verbose - Integer, set true if using
 *                          default messages.
 * Returns      : (non-verbose mode)
 *                0 - Ob1 can attack ob2.
 *                1 - Ob1 cannot see in the room.
 *                2 - Ob1 cannot see the target.
 *                3 - Ob1 doesn't have the dis to attack.
 *                4 - Ob1 is stunned.
 *                5 - Ob1 is attack_delayed
 *                6 - Ob2 is a ghost.
 *                7 - Ob2 has query_no_attack_me() defined.
 *                8 - Ob2 is not a living object.
 *                9 - Ob2 is not in the same room as ob1.
 *               10 - Ob2 has no_attack prop set.
 *               11 - Ob1's environment has no_attack prop.
 *               (verbose mode)
 *               An array consisting of two elements. The
 *               first will be the above described numbers,
 *               the second will be the default explanation
 *               of failure.
 */
public nomask mixed
can_attack(object ob1, object ob2, int verbose)
{
    string temp;

  /* First, make sure ob2 is a living target. */
    if (!ob2 || !objectp(ob2) || !living(ob2))
    {
        if (!verbose)
            return 8;
        return ({8, capitalize(ob2->short()) + " " +
            "is not alive to kill.\n"});
    }

  /* Next, make sure that ob2 is in ob1's environment. */
    if (environment(ob1) != environment(ob2))
    {
        if (!verbose)
            return 9;
        return ({9, "You can't attack something that " +
            "isn't here.\n"});
    }

  /* Next, make sure we can see in the room. */
    if (!ob1->can_see_in_room())
    {
        if (!verbose)
            return 1;
        temp = environment(ob1)->query_prop(ROOM_S_DARK_MSG);
        if (stringp(temp) && strlen(temp))
            return ({1, temp});
        return ({1, "It's too dark to see.\n"});
    }

  /* Next, make sure we can see the target. */
    if (!(ob2->check_seen(ob1)))
    {
        if (!verbose)
            return 2;
        return ({2, "You can see no such target.\n"});
    }

  /* Next, ensure ob1 has the dis to attack ob2. */
    if (!F_DARE_ATTACK(ob1, ob2))
    {
        if (!verbose)
            return 3;
        return ({3, "Umm... no, You do not have enough " +
            "self-discipline to dare!\n"});
    }

  /* Next make sure ob1 isn't stunned. */
    if (ob1->query_prop(LIVE_I_STUNNED))
    {
        if (!verbose)
            return 4;
        return ({4, "You are to stunned to attack!\n"});
    }

  /* Next make sure ob1 isn't attack_delayed */
    if (ob1->query_prop(LIVE_I_ATTACK_DELAY))
    {
        if (!verbose)
            return 5;
        return ({5, "You are unable to attack yet!\n"});
    }

  /* Fail if the target is a ghost. */
    if (ob2->query_ghost())
    {
        if (!verbose)
            return 6;
        return ({6, "You can't kill a ghost over again!\n"});
    }

  /* Fail if the target has query_not_attack_me() */
    if (ob2->query_not_attack_me())
    {
        if (!verbose)
            return 7;
        return ({7, ""});
    }

  /* Fail if the target possesses a no_attack prop. */
    temp = ob2->query_prop(OBJ_M_NO_ATTACK);
    if (temp)
    {
        if (!verbose)
            return 10;
        if (stringp(temp) && strlen(temp))
            return ({10, temp});
        return ({10, "You feel a divine force protecting " +
            "this being, your attack fails.\n"});
    }

  /* Fail if ob1's environment has no_attack prop. */
    temp = environment(ob1)->query_prop(ROOM_M_NO_ATTACK);
    if (temp)
    {
        if (!verbose)
            return 11;
        if (stringp(temp) && strlen(temp))
            return ({11, temp});
        return ({11, "You sense a divine force preventing " +
            "your attack.\n"});
    }

  /* We've exhausted all possible reasons a normal attack */
  /* may not proceed, so return 0 to allow attack. */
    return 0;
}
