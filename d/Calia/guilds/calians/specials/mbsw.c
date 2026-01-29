/*
 * Implementation of the Calian MBSW Special
 * This is a combination of the move behind and the swarm special
 *
 * Created by Petros, June 2008
 *
 */
#pragma strict_types

#include "defs.h"

inherit MB_ABILITY;

/*
 * Function name: on_move_behind_success
 * Description  : A hook for executing extra code when there is a success
 *                for move behind.
 * Arguments    : none
 * Returns      : nothing
 */
public void
on_move_behind_success()
{
    SWARM_ABILITY->do_ability("");
}

/*
 * Function name: on_already_move_behind_success
 * Description  : A hook for executing extra code when there is a success
 *                for move behind because they are not being attacked
 * Arguments    : player - player attempting to move behind
 * Returns      : nothing
 */
public void
on_already_move_behind_success(object player)
{
    SWARM_ABILITY->do_ability("");
}

/*
 * Function name: do_ability
 * Description  : The main entry point for abilities
 * Arguments    : arg - the argument passed in for targeting
 * Returns      : 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    return ::do_ability("behind " + arg);
}
