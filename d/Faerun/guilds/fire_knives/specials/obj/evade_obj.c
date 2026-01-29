#pragma strict_type

inherit "/d/Genesis/specials/std/evade_obj_base";

#include "../../guild.h"
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name("fireknives_evade");
    add_name( ({"fireknives_evade_object" }) );
    set_short("hidden fireknives evade object");    
    set_long("This is the secret and extremely hidden fireknives evade object.\n");
    
    setuid();
    seteuid(getuid());
    set_evade_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX, 
                        SKILL_WEIGHT, 20, TS_WIS }) );
    set_evade_skills( SS_ART );
    set_evade_combat_aid(52);
}


public int
is_fireknives_evade()
{
    return 1;
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
    object *onslaught;
    
    onslaught = filter(all_inventory(environment(player)),
                &operator(==)(,player) @ &->query_attack());
    
    if (!sizeof(onslaught))
        return 0;
    
    if (BLIND_ABILITY->query_ability_active(player) ||
        STUN_ABILITY->query_ability_active(player) || 
        EVISCERATE_ABILITY->query_ability_active(player) || 
        GAROTTE_ABILITY->query_ability_active(player) ||
        BACKSTAB_ABILITY->query_ability_active(player))
    {
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
    string  msg1, msg2,
            msg3;

    switch(random(3))
    {
    case 0:
        msg1 = "You watch as "+attacker->query_the_possessive_name(player) 
               +" swings at you and you calmly slide under the attack.\n";
               
        msg2 = player->query_the_name(attacker) 
               +" watches an incomming attack and calmly slides under it.\n";
               
        msg3 = "With a calm look, " + QTNAME(player) +
               " traces the swing of " + QTPNAME(attacker) +
               " and casually slides under it.\n";
        break;
    case 1:
        msg1 = "You see " + attacker->query_the_name(player) +
               " ready to aim a blow at you, and you quickly sidestep " +
               "the attack.\n";
               
        msg2 = player->query_The_name(attacker) + " sees you getting " +
               "ready to aim a blow at " + player->query_objective() +
               ", and sidesteps it towards the blow just as it strikes.\n";
               
        msg3 = QCTNAME(player) + " sees " + QTNAME(attacker) + 
               " getting ready to aim a blow at " + 
               player->query_objective() + ", sidesteps " +
               "the blow into the swing.\n";
        break;
    case 2:
        msg1 = "You spin into " + 
               attacker->query_the_possessive_name(player) +
               " attack, avoiding " + attacker->query_possessive() +
               " blow.\n";
               
        msg2 = player->query_The_name(attacker) + " spins into your " +
               "attack, avoiding your blow.\n";
               
        msg3 = QCTNAME(player) + " spins into " + QTPNAME(attacker) +
               " attack, avoiding " + attacker->query_possessive() + 
               " blow.\n";
        break;
    }
    
    player->catch_msg(msg1);
    attacker->catch_msg(msg2);
    player->tell_watcher(msg3, attacker, ({ player, attacker }));
}

