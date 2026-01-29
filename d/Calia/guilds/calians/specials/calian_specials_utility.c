/*
 * /d/Calia/guilds/calians/specials/calian_specials_utility.c
 *
 * Some utility functions to be used by the different calian
 * specials. Inherit this file in any calian special.
 *
 * Created by Petros, May 2008
 */

#pragma strict_types

#include <macros.h>
#include <options.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include "defs.h"

inherit CALIAN_UTILITY;

#include COUNCIL_HEADER
#include CALIAN_HEADER
#include DEBUGGER_TELL

/* 
 * Function:      special_tell_watcher 
 * Description:   Gives a combat message to those who "see blood". 
 *                This is rather like the standard tell_watcher 
 *                function but takes into account the Calian 
 *                "see specials" option. 
 * Arguments:     object tp    - the hitter 
 *                string str   - message 
 *                object enemy - the living getting hit 
 *                mixed notell - those not to tell the message 
 */ 
public void
special_tell_watcher(object tp, string str, object enemy, mixed notell)
{
    object *ob; 
    int i, size; 

    ob = all_inventory(environment(tp)) - ({ tp, enemy }); 

    if (pointerp(notell)) 
        ob -= notell; 

    /* We only display combat messages to interactive players. */ 
    ob = FILTER_PLAYERS(ob); 

    i = -1; 
    size = sizeof(ob); 

    while(++i < size) 
    { 
        if ((!ob[i]->query_option(OPT_NO_FIGHTS) ||
             (ob[i]->query_skill(CALIAN_OPTIONS) & CALOPT_SEE_SPECIALS)) 
             && CAN_SEE_IN_ROOM(ob[i])) 
        { 
            if (CAN_SEE(ob[i], tp))
            { 
                ob[i]->catch_msg(str); 
            }
        }
    }
}

/* 
 * Function:      calian_special_notify_fail 
 * Description:   If the argument "as_tell" is 1, tell the player 
 *                the message directly, otherwise this function 
 *                behaves just like the notify_fail efun. 
 * Arguments:     string msg  - the message 
 *                object tp   - this player 
 *                int as_tell - whether to send as tell or not 
 * Returns:       int - 1 if sent as tell, 0 otherwise. 
 * 
 */ 
public varargs int 
calian_special_notify_fail(string msg, object tp, int as_tell) 
{ 
    if (as_tell) 
    { 
        tell_object(tp, msg); 
        return 1; 
    } 
    notify_fail(msg); 
    return 0; 
} 

/* 
 * Function:     is_attacking 
 * Description:  Should return whether the player is attacking  
 *               the enemy (1 for yes, 0 for no). 
 * Arguments:    object player - who is attacking 
 *               object enemy  - who is attacked 
 * Returns:      int - success 
 */ 
public int 
is_attacking(object player, object enemy) 
{
    return (player->query_attack() == enemy); 
}

/* 
 * Function:     is_attacking_this_living 
 * Description:  Should return whether enemy attacks player. 
 * Arguments:    object enemy    -  the enemy 
 *               object player   -  the possible victim 
 * Returns:      1 if enemy is attacking player, 0 otherwise. 
 */ 
int 
is_attacking_this_living(object enemy, object player) 
{ 
    return enemy->query_attack() == player; 
} 

/* 
 * Function:     is_sustaining_attack 
 * Description:  Should return whether enemy attacks player for more than
 *               2 seconds 
 * Arguments:    object enemy    -  the enemy 
 *               object player   -  the possible victim 
 * Returns:      1 if enemy is attacking player, 0 otherwise. 
 */ 
public int 
is_sustaining_attack(object enemy, object player) 
{
    int last_attack_time;
    
    if (enemy->query_attack() != player)
    {
        return 0;
    } 
    
    // If the enemy is attacking this player, then we check the properties
    // which should have been set as to when the last attack was.
    last_attack_time = enemy->query_prop(CALIAN_ATTACKER_LAST_ATTACK_TIME);
    if (last_attack_time && (last_attack_time + 2) <= time())
    {
        // More than 2 seconds have passed since the attack was made
        return 1;
    }
    
    return 0;
} 
