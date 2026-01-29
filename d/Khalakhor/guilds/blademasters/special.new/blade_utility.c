/*
 * Blademasters Utility Functions
 *
 * Keep all the utility functions used by various objects here.
 *
 * Created by Petros, July 2009
 */

#pragma no_clone
#pragma strict_types

#include <ss_types.h>
#include <wa_types.h>

#include "defs.h"

/*
 * Function:    is_skilled_blademaster
 * Description: This function checks whether the blademaster is
 *              qualified to use his abilities or not.
 */
int
is_skilled_blademaster(object player)
{
    if (player->query_skill(SS_WEP_SWORD) < REMAIN_SWORD_SKILL)
    {
        return 0;
    }
    
    return 1;
}

varargs object *
get_swords (object player=TP)
{
  return filter(player->query_weapon(-1),
                &operator(==)(W_SWORD) @ &->query_wt());
}
