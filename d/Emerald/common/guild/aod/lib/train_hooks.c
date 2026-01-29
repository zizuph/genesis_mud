/*
 *  /d/Emerald/common/guild/aod/lib/train_hooks.c
 *
 *  These hooks are used in the various training rooms for the Army of
 *  Darkness guild.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

/*
 * Function name: sk_hook_unknown_skill
 * Description  : Player tries to improve or learn an unknown skill.
 * Arguments    : string skill - The skill he sought for.
 *                string verb  - 'learn' or 'improve'.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_unknown_skill(string skill, string verb)
{
    notify_fail("There is no skill named '" + skill + "' to " + verb + ".\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " bellows: Huh?? I not train that"
          + " skill! NOT TRICK TRAINERS!!\n");
    }

    return 0;
} /* sk_hook_unknown_skill */



/*
 * Function name: sk_hook_improve_unknown
 * Description  : Player wants to improve a skill he has never learned.
 * Arguments    : string skill - the skill the player tried to improve.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_improve_unknown(string skill)
{
    notify_fail("You must learn a skill before you can improve it.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " bellows: No! Not how we do it!"
          + " How you improve what you not even <learn>? LEARN"
          + " FIRST!!\n");
    }

    return 0;
} /* sk_hook_improve_unknown */


/*
 * Function name: sk_hook_learn_known
 * Description  : Player wants to learn an already known skill.
 * Arguments    : string skill - the skill the player tried to learn.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_learn_known(string skill)
{
    notify_fail("You already know that skill, try to improve it.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " bellows: Huh? You so dumb you"
          + " even trick self??! You already learn! IMPROVE IMPROVE!\n");
    }

    return 0;
} /* sk_hook_learn_known */


/*
 * Function name: sk_hook_cant_pay
 * Description  : Player cannot pay for session. (Kill him?)
 * Arguments    : string skill  - the skill the player tries to improve.
 *                int to_lev - the level to wich the player wanted training.
 *                int cost - the price that is required, in coppers.
 * Returns      : int 0 - as always with notify_fail.
 */
int
sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    notify_fail("You do not have enough money with you.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " bellows: No money, no train!"
          + " That very BAD trick! Me almost want smash face!\n");
    }

    return 0;
} /* sk_hook_cant_pay */


/*
 * Function name: sk_hook_no_list_learn
 * Description  : This hook is called when there are no more skills the
 *                player can learn here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_learn()
{
    if (NPC)
    {
        write("The " + NPC + " bellows: All skills learned. Maybe"
          + " try <improve> or go ask other trainer.\n");
    }
    else
    {
        write("You have learned all of the available skills trained here."
          + " Perhaps you could try to <improve> some of the skills you"
          + " have learned.\n");
    }

    return 1;
} /* sk_hook_no_list_learn */


/*
 * Function name: sk_hook_no_list_improve
 * Description  : This hook is called when there are no more skills the
 *                player can improve here.
 * Returns      : int 1 - as always after a command succeeds.
 */
int
sk_hook_no_list_improve()
{
    if (NPC)
    {
        write("The " + NPC + " bellows: No training! Maybe <learn>"
          + " new skill or ask other trainer to teach.\n");
    }
    else
    {
        write("There are no skills you can improve in this guild."
          + " Perhaps you would feel like learning some new skills,"
          + " or try to find a new guild elsewhere?\n");
    }

    return 1;
} /* sk_hook_no_list_improve */


/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:     skill - The skill player wanted to improve
 * Returns:       0
 */
int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have " +
        "to seek knowledge elsewhere.\n");

    if (NPC)
    {
        notify_fail("The " + NPC + " bellows: No more improve! You"
          + " all trained! Maybe try other trainer if want different"
          + " skill. Go smash faces! Army! Army!! ARMY!!!\n");
    }

    return 0;
} /* sk_hook_improved_max */
