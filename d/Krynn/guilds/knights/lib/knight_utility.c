/*
 * Utility Functions for Knight Specials
 *
 * This file contains common functions used by many abilities. This
 * will be inherited in those that need it.
 *
 * Created by Petros, November 2008
 */
 
#pragma strict_types

#include "../guild.h"

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "/std/combat/combat.h"

// Prototypes
public object       query_solamnian_steed(object player);
public object       query_shield(object actor, int location);
public object       query_primary_weapon(object actor, int allow_shield = 1);

/*
 * Function:    query_mounted_solamnian_steed
 * Description: Returns the steed that the Knight is riding on if it
 *              is a Solamnian warhorse
 * Arguments:   player - the knight to query for a steed
 * Returns:     the horse object or 0
 */
public object
query_mounted_solamnian_steed(object player)
{
    object steed;
    
    // We want the Knight to be able to mount any solamnian
    // steed and use it as a part of the specials. This allows for
    // roleplay instances where your superior loses his/her steed
    // and you can offer it to them.
    steed = player->query_prop(LIVE_O_STEED);
    if (objectp(steed) && steed->is_solamnian_steed())
    {
        return steed;
    }
    
    return 0;
}

/*
 * Function:    query_solamnian_steed
 * Description: Returns the steed that belongs to the Knight. NOT necessarily
 *              the one that he is riding on.
 * Arguments:   player - the knight to query for a steed
 * Returns:     the horse object or 0
 */
public object
query_solamnian_steed(object player)
{
    object horse;
    
    setuid();
    seteuid(getuid());

    horse = MOUNT_MANAGER->query_solamnian_steed(player);
    
    return horse;
}

/*
 * Function:    query_shield
 * Description: Function to return the shield, if worn, of Knight
 *              Can optionally return the shield for a particular
 *              location
 * Arguments:   actor - Knight to be checked
 *              location (optional) - which hand to check for a shield
 * Returns:     shield object
 */
public object
query_shield(object actor, int location)
{
    object shield;
    
    if (!location)
    {
        // We just return the shield if it's worn on the
        // left or right hands
        shield = actor->query_armour(W_RIGHT);
        if (!objectp(shield))
        {
            shield = actor->query_armour(W_LEFT);
        }
    }
    else
    {
        shield = actor->query_armour(location);
    }
    
    if (objectp(shield)
        && shield->query_at() == A_SHIELD)
    {
        return shield;
    }
        
    return 0;
}

/*
 * Function:    query_primary_weapon
 * Description: Function to return the primary weapon (as set in options)
 *              of the Knight. It can even be a shield.
 * Arguments:   actor - Knight to be checked
 *              allowshield - allow a shield to be a weapon
 * Returns:     weapon or shield to be used in attacks.
 */
public object
query_primary_weapon(object actor, int allow_shield = 0)
{
    object weapon, medal;
    int primary_hand, preferred, nonpreferred;
    
    // If the Knight is wielding a two-handed weapon, then just return
    // it.
    if (actor->query_weapon(W_BOTH))
    {
        return actor->query_weapon(W_BOTH);
    }
    
    primary_hand = 0;
    medal = present("pal_med", actor);
    if (medal)
    {
        primary_hand = medal->query_primary();
    }

    // We *prefer* the primary weapon. But we will take any other
    // weapon as well. If shields are allowed, that means also
    // that if you have a shield in your primary and a weapon in
    // your non-primary, it'll use the shield.
    if (primary_hand == 0) // right hand
    {
        preferred = W_RIGHT;
        nonpreferred = W_LEFT;
    }
    else
    {
        preferred = W_LEFT;
        nonpreferred = W_RIGHT;
    }

    weapon = actor->query_weapon(preferred);
    if (allow_shield && !objectp(weapon))
    {
        weapon = query_shield(actor, preferred);
    }
    
    // If the primary hand doesn't have a weapon, check the
    // offhand to see if it can supply a weapon.
    if (!objectp(weapon))
    {
        weapon = actor->query_weapon(nonpreferred);
        if (allow_shield && !objectp(weapon))
        {
            weapon = actor->query_shield(actor, nonpreferred);
        }
    }
    
    return weapon;
}
