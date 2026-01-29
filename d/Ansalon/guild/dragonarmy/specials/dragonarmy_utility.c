/*
 * Utility Functions for the Dragonarmy
 *
 * This file will include commonly used functions, and will be inherited
 * by dragonarmy abilities to support those abilities.
 *
 * Created by Petros, February 2009
 *
 * Modifications:
 * 9/27/2011 - fixed the caid level adjustment to not go above 100 (Petros)
 */
 
#pragma strict_types

#include "defs.h"

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

public object
query_summoned_strike_dragon(object actor)
{
    setuid();
    seteuid(getuid());
    
    return DRAGONS_MANAGER->query_summoned_strike_dragon(actor);
}

public object
query_present_summoned_strike_dragon(object actor)
{
    object dragon;
    
    if (objectp(dragon = query_summoned_strike_dragon(actor))
        && environment(dragon) == environment(actor))
    {
        return dragon;
    }
    
    return 0;
}

public object
query_summoned_dragonsteed(object actor)
{
    setuid();
    seteuid(getuid());
    
    return DRAGONS_MANAGER->query_summoned_dragonsteed(actor);
}

public object
query_summoned_dragon(object actor)
{
    object dragon;
    
    if (objectp(dragon = query_summoned_strike_dragon(actor))
        || objectp(dragon = query_summoned_dragonsteed(actor)))
    {
        return dragon;
    }
    
    return 0;
}

public int
query_is_strike_dragon(object dragon)
{
    if (MASTER_OB(dragon) == STRIKE_DRAGON)
    {
        return 1;
    }
    
    return 0;
}

public int
query_is_dragonsteed(object dragon)
{
    if (MASTER_OB(dragon) == DRAGON_STEED)
    {
        return 1;
    }
    
    return 0;
}

public int
query_level_caid_adjustment(object player)
{
    int base = 90;
    int promotion_level = player->query_dragonarmy_promotions();
    
    // Officers and above have the maximum aid possible.
    return base += min(100 - base, max(0, promotion_level * 5));
}

/*
 * Function:    remove_summoned_strike_dragon
 * Description: This function is called to remove a pending dragon.
 *              A pending dragon occurs when the time expires on the dragon
 *              in the middle of an ability. The dragon should stick around
 *              until after the ability executes and then be removed.
 */
public void
remove_summoned_strike_dragon(object player)
{
    object dragon;
    
    dragon = query_summoned_strike_dragon(player);
    if (objectp(dragon))
    {        
        dragon->remove_object();
    }
}
