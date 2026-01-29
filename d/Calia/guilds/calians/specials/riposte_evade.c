/*
 * Riposte Effect Object
 * 
 * Calian Riposte is a parry skill that deflects attacks and scores
 * a hit on the attacker. Here are the conditions
 *   a) The effect has base 20% chance of evading
 *   b) Attack can only happen once every 5 seconds (once a round)
 *   c) It uses to_hit value of 70 (66% chance)
 *   d) The attack is only effective against the person one is
 *      attacking.
 *   e) Can't be stunned or delayed
 *   f) Has to be able to see the attacker
 *   g) sword or polearm must be wielded
 *
 * Adapted by Petros from the original Calian code, June 2008
 */
 
#pragma strict_types

#include "defs.h"

// Riposte Object is both an evade object as well as a damage special
inherit EVADE_BASE_OBJ;
inherit SPECIALS_UTILITY;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include DEBUGGER_TELL
#include CALIAN_HEADER

/*
 * Function     : is_riposte_evade
 * Description  : Easy way to identify a riposte evade object
 * Arguments    : none
 * Returns      : 1 - always returns true
 */
public int
is_riposte_evade()
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
    set_name("_calian_riposte_object_");
    add_name( ({"calian_riposte_object" }) );
    set_short("hidden calian riposte object");    
    set_long("The object that grants riposte to a Calian. One should not "
           + "be able to see it in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_evade_stats( TS_DEX );
    set_evade_skills( ({ SKILL_AVG, SS_PARRY, SS_CALIAN_RIPOSTE_SKILL, 
                         SKILL_END }) );
    // 25% combat aid == 20% evade
    set_evade_combat_aid(RIPOSTE_EVADE_CAID);
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
    
    // If the Calian's swarm is active, riposte evade should not be
    // active.
    if (SWARM_ABILITY->query_ability_active(player))
    {
        send_debug_message("riposte_evade", "Cannot use riposte evade when "
            + "swarm is active.");
        return 0;
    }

    weapon = player->query_calian_main_weapon();
    if (!objectp(weapon))
    {
        send_debug_message("riposte_evade", "Cannot riposte without a "
                         + "weapon.");
        // No weapon wielded by Calian.
        return 0;
    }
    
    if (!CAN_SEE(player, attacker))
    {
        send_debug_message("riposte_evade", "Cannot riposte since the "
                         + "opponent cannot be seen.");
        //Can't see who we're fighting: no riposte.
        return 0;        
    }
    
    if (!((weapon->query_wt() == W_SWORD )
        || (weapon->query_wt() == W_POLEARM)))
    {
        send_debug_message("riposte_evade", "Cannot riposte with a weapon "
                         + "that is not a sword or a polearm.");        
        // Not wielding a sword or polearm.
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
    string calian_msg, attacker_msg, watcher_msg;
    object * attacker_weps;
    object calian_wep, attacker_wep;
    
    if (player->query_attack() != attacker)
    {
        calian_msg = capitalize(attacker->query_The_name(player))
            + " attacks you from the side, but you step back quickly and "
            + "all you feel is a rush of air.";
        attacker_msg = "You attack " + player->query_the_name(attacker)
            + " from the side, but " + player->query_pronoun() 
            + " steps back quickly and your blow falls short.";
        watcher_msg = QCTNAME(attacker) + " attacks " + QTNAME(player)
            + " from the side, but " + player->query_pronoun() 
            + " steps back quickly and the blow falls short.";
        player->catch_msg(calian_msg + "\n");
        attacker->catch_msg(attacker_msg + "\n");
        special_tell_watcher(player, watcher_msg + "\n", attacker, 0);        
        return;
    }
    
    seteuid(getuid());
    if (RIPOSTE_ATTACK->query_ability_in_cooldown(player))
    {
        calian_wep = player->query_calian_main_weapon();
        attacker_wep = 0;
        attacker_weps = attacker->query_weapons(-1);
        if (sizeof(attacker_weps) > 0)
        {
            attacker_wep = attacker_weps[0];
        }
        // We should print out some sort of evade message here.
        RIPOSTE_ATTACK->print_riposte_attack(player, attacker, 
                                             attacker_wep, calian_wep, 
                                             0, 1);
        send_debug_message("riposte_evade", "Attack parried, cannot "
                         + "execute riposte attack so soon.");
        return;
    }
    
    send_debug_message("riposte_evade", "Attack parried, executing "
                     + "riposte attack.");
    object oldtp = this_player();
    set_this_player(player);                   
    RIPOSTE_ATTACK->do_ability("");
    set_this_player(oldtp);
}
