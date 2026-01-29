/*
 * Militia Evade Effect Object
 * 
 * Adapted by Petros from the original Militia code, September 2008
 *
 * Modified caid from 42 to 40 following global layman guild review.
 * -Arman (AoB) 6 August 2019
 */
 
#pragma strict_types

#include "defs.h"

inherit EVADE_OBJ_BASE;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include DEBUGGER_LIB

// Defines

/*
 * Function     : is_militia_evade
 * Description  : Easy way to identify a militia evade object
 * Arguments    : none
 * Returns      : 1 - always returns true
 */
public int
is_militia_evade()
{
    return 1;
}

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_militia_evade_object_");
    add_name( ({"militia_evade_object" }) );
    set_short("hidden militia evade object");    
    set_long("The object that grants Evade to Militia. One should not "
           + "be able to see it in their inventory.\n");

    setuid();
    seteuid(getuid());

    // Original evade was based on encumberence and weight, so I added
    // TS_STR to the list of stats used. TS_WIS and TS_DEX make sense
    // for general evade purposes.
    set_evade_stats( ({ SKILL_AVG, TS_DEX, TS_STR, TS_WIS, SKILL_END }) );    
    // because militia tactics is trainable to 50 only, we double weight
    // it for the calculation to get an even 100.
    set_evade_skills( ({ SKILL_WEIGHT, 200, SS_MILITIA }) );
    set_evade_combat_aid(40);
}                           

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{ 
    object weapon;   
    
    if (!EVADE_ABILITY->query_ability_active(player))
    {
        // A militia person must be in "evade" mode in order for
        // this evade to be valid.
        send_debug_message("militia_evade", 
            capitalize(player->query_real_name()) + " is not in evade "
          + "mode.");
        return 0;
    }
    
    if (JAB_ABILITY->query_ability_active(player))
    {
        // Can't evade attacks when jabbing.
        send_debug_message("militia_evade",
            capitalize(player->query_real_name()) + " is jabbing and "
          + "cannot evade.");        
        return 0;
    }
    
    return 1;
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    object * wep;
    string weapon, msg1, msg2, msg3;
    
    wep = player->query_weapon(-1);

    if (!sizeof(wep))
    {
        switch(random(2))
        {
        case 0:
            msg1 = "You duck beneath " + 
                attacker->query_the_possessive_name(player) + " clumsy " +
                "attempt to strike you.\n";
            msg2 = player->query_The_name(attacker) + " ducks beneath " +
                "your clumsy swing.\n";
            msg3 = QCTNAME(player) + " easily ducks " + QTPNAME(attacker) +
                " clumsy swing.\n";
            break;

        default:
            msg1 = "You lean away from " + 
                attacker->query_the_possessive_name(player) + " swing, and " +
                "watch as it cleaves only air.\n";
            msg2 = player->query_The_name(attacker) + " leans back and " +
                "watches you thrash harmlessly at the air.\n";
            msg3 = QCTNAME(player) + " leans back and lets " +
                QTNAME(attacker) + " thrash at the air.\n";
        }
    }
    else
    {
        weapon = wep[0]->short();

        switch(random(4))
        {
        case 0:
            msg1 = "You duck beneath " + 
                attacker->query_the_possessive_name(player) + " clumsy " +
                "attempt to strike you.\n";
            msg2 = player->query_The_name(attacker) + " ducks beneath " +
                "your clumsy swing.\n";
            msg3 = QCTNAME(player) + " easily ducks " + QTPNAME(attacker) +
                " clumsy swing.\n";
            break;

        case 1:
            msg1 = "You lean away from " + 
                attacker->query_the_possessive_name(player) + " swing, and " +
                "watch as it cleaves only air.\n";
            msg2 = player->query_The_name(attacker) + " leans back and " +
                "watches you thrash harmlessly at the air.\n";
            msg3 = QCTNAME(player) + " leans back and lets " +
                QTNAME(attacker) + " thrash at the air.\n";
            break;

        case 2:
            msg1 = "You point your " + weapon + " at " + 
                attacker->query_the_name(player) + ", preventing " +
                attacker->query_objective() + " from getting within striking " +
                "distance.\n";
            msg2 = player->query_The_name(attacker) + " points " +
                player->query_possessive() + " " + weapon + " at your " +
                "chest, preventing you from getting close enough to " +
                "strike.\n";
            msg3 = QCTNAME(player) + " points " + 
                player->query_possessive() + " " + weapon + " at " + 
               QTNAME(attacker) + ", preventing " + attacker->query_objective() +
               " from getting within striking distance.\n";
            break;

        default:
            msg1 = "You sweep aside " + 
                attacker->query_the_possessive_name(player) + " clumsy " +
                "blow with the butt of your " + weapon + ".\n";
            msg2 = player->query_The_name(attacker) + " sweeps aside " +
                "your clumsy blow with the butt of " + 
                player->query_possessive() + " " + weapon + ".\n";
            msg3 = QCTNAME(player) + " sweeps aside " + QTPNAME(attacker) +
                " clumsy blow with the butt of " + 
                player->query_possessive() + " " + weapon + ".\n";
            break;

        }

    } 

    player->catch_tell(msg1);           /* Send message to evader */
    attacker->catch_tell(msg2);               /* Send message to evader */
    player->tell_watcher(msg3, attacker); /* Send message to watchers */
    log_file("militia_evade", extract(ctime(time()), 4, 15) +
        capitalize(player->query_real_name()) + " evaded " + 
        capitalize(attacker->query_real_name()) + "\nFile: " + 
        file_name(attacker) + ".\nEnemy Avg: " +
        attacker->query_average_stat() + ", Evader Avg: " + 
        player->query_average_stat() + " Evader skill: " +
        player->query_skill(SS_MILITIA) + ".\n");
}

