/*
 * Reflect Effect Object
 * 
 * This is the base reflect effect object that handles reflect in conjunction
 * with the reflect shadow. reflect objects stack with one another.
 *
 * Modified from Evade Effect Object created by Petros.
 * Created by Carnak January 2018
 */
 
#pragma strict_types

#include "defs.h"

inherit EFFECT_BASE_OBJ;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#include "../debugger/debugger_tell.h"

#define REFLECT_SUBLOC          "_reflect_spell_effect_subloc"

// Prototypes
public void         set_reflect_combat_aid(int caid);

// Global Variables
public int          g_bAllowSpecials = 1;
public int          g_bAllowMagicAttacks = 1;
public int          g_bAllowWhiteAttacks = 1;
public int          g_damageType = MAGIC_DT;
public int          g_nLikelihood = 100;
public int *        g_excludedTargetHitLocations = ({ });
public string *     g_resistance_types = ({ MAGIC_I_RES_MAGIC });
public function     Reflect_function = 0;


/*
 * Function:    set_excluded_target_hit_locations
 * Description: Sets up the locations that should not reflect damage. The
 *              argument is an integer array of the hit locations.
 */
public void      
set_excluded_target_hit_locations(int * excludedTargetHitLocations)
{
    if (sizeof(excludedTargetHitLocations))
    {
        g_excludedTargetHitLocations = excludedTargetHitLocations + ({ });
    }
    else
    {
        g_excludedTargetHitLocations = ({ });
    }
}

/*
 * Function:    query_allow_target_hitloc
 * Description: The argument target_hitloc is the hitloc that actually hit
 *              the player. Here we determine whether the reflective damage
 *              will occur based on where it hit. For example, if the effect
 *              only applies when A_HEAD is the target hitloc, then a check
 *              will check for A_HEAD.
 */
public int
query_allow_target_hitloc(int target_hitloc)
{
    // The default implementation of this function is to allow everything
    // unless it is specifically excluded.
    return !IN_ARRAY(target_hitloc, g_excludedTargetHitLocations);
}

/*
 * Function:    set_reflect_damage_likelihood
 * Description: Sets the percentage chance that the reflect damage will
 *              actually happen.
 */
public void
set_reflect_damage_likelihood(int likelihood)
{
    g_nLikelihood = max(1, min(100, likelihood));
}

/*
 * Function:    query_reflect_damage_likelihood
 * Description: Returns the percentage chance that the reflect damage will
 *              actually happen.
 */
public int
query_reflect_damage_likelihood()
{
    return g_nLikelihood;
}

/*
 * Function:    set_reflect_damage_type
 * Description: Sets the damage type that should be inflicted on the attacker.
 *              Should be one of the values defined in /sys/wa_types.h.
 */
public void
set_reflect_damage_type(int damageType)
{
    g_damageType = damageType;
    switch (g_damageType)
    {
    case W_IMPALE:
    case W_SLASH:
    case W_BLUDGEON:
    case MAGIC_DT:
        break;
    
    default:
        // Ensure that if an invalid type gets set, we set it correctly.
        g_damageType = MAGIC_DT;
    }
}

/*
 * Function:    query_reflect_damage_type
 * Description: Returns the damage type that should be inflicted on attacker
 */
public int
query_reflect_damage_type()
{
    return g_damageType;
}

/*
 * Function:    set_allow_specials
 * Description: Usually called in the initialize_shadow function. This set
 *              whether the reflective damage will apply when specials
 *              are executed against this player.
 */
public void
set_allow_specials(int bAllowSpecials)
{
    g_bAllowSpecials = bAllowSpecials;
}

/*
 * Function:    query_allow_specials
 * Description: Returns whether reflective damage will apply when specials
 *              are executed against this player
 */
public int
query_allow_specials()
{
    return g_bAllowSpecials;
}

/*
 * Function:    set_allow_magic_attacks
 * Description: Usually called in the initialize_shadow function. This sets
 *              whether the reflective damage will apply when the attack
 *              is a magic attack, like a spell.
 */
public void
set_allow_magic_attacks(int bAllowMagicAttacks)
{
    g_bAllowMagicAttacks = bAllowMagicAttacks;
}

/*
 * Function:    query_allow_magic_attacks
 * Description: Returns whether reflective damage will apply when the attack
 *              is a magic attack, like a spell.
 */
public int
query_allow_magic_attacks()
{
    return g_bAllowMagicAttacks;
}

/*
 * Function:    set_allow_specials
 * Description: Usually called in the initialize_shadow function. This set
 *              whether the reflective damage will apply when specials
 *              are executed against this player.
 */
public void
set_allow_white_attacks(int bAllowWhiteAttacks)
{
    g_bAllowWhiteAttacks = bAllowWhiteAttacks;
}

/*
 * Function:    query_allow_specials
 * Description: Returns whether reflective damage will apply when specials
 *              are executed against this player
 */
public int
query_allow_white_attacks()
{
    return g_bAllowWhiteAttacks;
}

/*
 * Function:    set_reflect_resistance_types
 * Description: Allows the setting of the types of resistances that
 *              should be checked when dealing magic damage.
 */
public void     
set_reflect_resistance_types(string * resistances)
{
    if (!sizeof(resistances))
    {
        g_resistance_types = ({ MAGIC_I_RES_MAGIC });
    }
    else
    {
        g_resistance_types = resistances;
        if (!IN_ARRAY(MAGIC_I_RES_MAGIC, g_resistance_types))
        {
            g_resistance_types += ({ MAGIC_I_RES_MAGIC });
        }
    }
}

/*
 * Function:    query_reflect_resistance_types
 * Description: Returns the types of resistances that should be
 *              checked whenever magic damage is being dealt
 */
public string *
query_reflect_resistance_types()
{
    return g_resistance_types;
}

/*
 * Function     : set_reflect_skills
 * Description  : Set the skills that will be used in calculating
 *                the strength of the reflect
 * Arguments    : skills
 * Returns      : nothing
 */
public nomask void 
set_reflect_skills(mixed skills)
{
    set_effect_skills(skills);
}

/*
 * Function     : query_reflect_skills
 * Description  : Returns the skills being used to calculate reflect strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public mixed 
query_reflect_skills()
{
    return query_effect_skills();
}

/*
 * Function     : set_reflect_stats
 * Description  : Set the stats that will be used in calculating
 *                the strength of the reflect
 * Arguments    : stats
 * Returns      : nothing
 */
public nomask void 
set_reflect_stats(mixed stats)
{
    set_effect_stats(stats);
}

/*
 * Function     : query_reflect_stats
 * Description  : Returns the stats being used to calculate reflect strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public mixed 
query_reflect_stats()
{
    return query_effect_stats();
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
    set_name("_base_reflect_object_");
    add_name( ({"base_reflect_obj" }) );
    set_short("hidden base reflect object");    
    set_long("A basic reflect object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    // By default, it doesn't modify by skills nor stats
    set_reflect_stats( TS_DEX );
    set_reflect_skills( SS_DEFENCE );
    // 25% combat aid == 20% reflect
    set_reflect_combat_aid(25);
}

/*
 * Function     : set_reflect_combat_aid
 * Description  : Sets the reflect combat aid which is used to determine
 *                the reflect percentage
 * Arguments    : combat aid number
 * Returns      : nothing
 */
public nomask void
set_reflect_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
}

/*
 * Function     : query_reflect_combat_aid
 * Description  : returns the reflect combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_reflect_combat_aid(object player)
{
    return ::query_effect_combat_aid(player);
}

/*
 * Function     : query_effect_combat_aid
 * Description  : returns the effect combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public nomask int
query_effect_combat_aid(object player)
{
    return query_reflect_combat_aid(player);
}

/*
 * Function     : query_reflect_percentage
 * Description  : Returns the max percentage set during creation
 * Arguments    : none
 * Returns      : the evasion percentage
 */
public nomask int 
query_reflect_percentage(object player)
{
    return query_effect_percentage(player);
}

/*
 * Function     : query_reflect_strength
 * Description  : Function that will be used to gauge the strength of
 *                the reflect based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the evasion percentage
 */
public int
query_reflect_strength(object player, object attacker, int attack_id)
{
    return min(query_effect_percentage(player),
        ::query_effect_strength(player, attacker, attack_id));
}    

/*
 * Function     : query_effect_strength
 * Description  : Function that will be used to gauge the strength of
 *                the effect based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the effect percentage
 */
public nomask int
query_effect_strength(object player, object attacker, int attack_id)
{
    return query_reflect_strength(player, attacker, attack_id);
}

/*
 * Function     : query_reflect_valid
 * Description  : Validation function to see whether this reflect object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_reflect_valid(object player, object attacker, int attack_id)
{
    return 1;
}

/*
 * Function:    set_reflected_function
 * Description: A person who creates the reflect object can define their own
 *              function that they want called when the reflect happens.
 *              Call this to set it and have custom descriptions.
 */
public void
set_reflected_function(function func)
{
    Reflect_function = func;
}

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_reflect_damage_description(object player, object attacker, mixed results)
{
    if (functionp(Reflect_function))
    {
        // If a custom block function has been defined, we use that instead.
        Reflect_function(player, attacker, results);
        return;
    }
    
    attacker->catch_msg("Your attack on " + QTNAME(player) + " ends up "
        + "hurting you also.\n");
    player->catch_msg("The attack on you by " + QTNAME(attacker)
        + " backfires and ends up hurting " + attacker->query_objective()
        + " also.\n");
    tell_room(environment(player), QCTNAME(attacker) + " is hurt by some "
        + "reflected damage from " + QTNAME(player) + ".\n", 
        ({ attacker, player }));
}

/*
/*
 * Function name: remove_reflect_effect
 * Description:   Remove this reflect from a target, also removing the reflect
 *                shadow as needed
 * Arguments:     object target - the one affected by the reflect
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_reflect_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        send_debug_message("base_reflect", "Master object, will not process "
        + "shadow check.");
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_reflect_effect(this_object());
    if (!sizeof(target->query_reflect_effects()) 
        && target->has_reflect_shadow())
    {
        send_debug_message("base_reflect", "Removing shadow because there "
        + "are no more effects.");
        target->remove_reflect_shadow();
    }
    return 1;
}

/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This will need to
 *                be done so that the shadow can be properly removed
 *                when there are no more effects.
 * Arguments:     none
 * Returns:       nothing
 */
public void
remove_object()
{
    foreach (object shadowobj : query_shadow_list())
    {
        remove_reflect_effect(shadowobj->query_shadow_who());
    }
    ::remove_object();
}

/*
/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    remove_object();
    return ::dispel_effect(dispeler);
}
    

/*
 * Function name: add_reflect_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int
add_reflect_effect(object target)
{
    if (target && living(target))
    {
        if (!target->has_reflect_shadow())
        {
            send_debug_message("base_reflect", 
                               "Did not find shadow, creating shadow.");
            clone_object(REFLECT_SH)->shadow_me(target);
        }
        else
        {
            send_debug_message("base_reflect", "Found reflect shadow.");
        }
        
        target->add_reflect_effect(this_object());
        return 1;
    }    
    return 0;
}


/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    add_reflect_effect(query_effect_target());
    return 1;
}