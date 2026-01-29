/*
 */

#pragma strict_types

#include "../guild.h"

inherit QUICKSHOT;

/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Returns:         number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    return 100;
} /* query_combat_aid_modifier */

/*
 * Function name:   query_tohit
 * Description:     Calculates the tohit for the player. Based on the missile
 *                  knowledge or fixed hitchance, this is lowered to allow the
 *                  archer to more easily raise the missile knowledge.
 * Arguments:       none
 * Returns:         input to cb_tohit function
 */
public int
query_tohit()
{
    return 90;
} /* query_tohit */