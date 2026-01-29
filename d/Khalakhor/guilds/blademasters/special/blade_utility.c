/*
 * Blademasters Utility Functions
 *
 * Keep all the utility functions used by various objects here.
 *
 * Created by Petros, July 2009
 */

#pragma strict_types

#include "defs.h"
#include <ss_types.h>

/*
 * Function:    is_skilled_blademaster
 * Description: This function checks whether the blademaster is
 *              qualified to use his abilities or not.
 */
public int
is_skilled_blademaster(object player)
{
    if (player->query_skill(SS_WEP_SWORD) < REMAIN_SWORD_SKILL)
    {
        return 0;
    }
    
    return 1;
}
