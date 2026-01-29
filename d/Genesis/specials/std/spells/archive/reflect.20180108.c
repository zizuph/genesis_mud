/*
 * General Reflect Damage Spell
 * 
 * This is a generic reflect damage spell that should be used as the basis for all
 * reflection spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, September 2012
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include <wa_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Global Variables
public int      g_bAllowSpecials = 0;
public int      g_bAllowMagicAttacks = 0;
public int *    g_excludedTargetHitLocations = ({ });
public int      g_nCombatAid = 25;
public int      g_damageType = MAGIC_DT;
public int      g_nLikelihood = 75;

// Function Declarations
public void     resolve_reflect_spell(object caster, mixed * targets, int * resist, int result);
public string * query_reflect_ingredients(object caster);
public void     set_allow_specials(int bAllowSpecials);
public void     set_allow_magic_attacks(int bAllowMagicAttacks);
public void     set_excluded_target_hit_locations(int * excludedTargetHitLocations);
public void     set_reflect_damage_combat_aid(int nCombatAid);
public void     set_reflect_damage_type(int damageType);
public void     set_reflect_damage_likelihood(int likelihood);
public int      query_allow_specials();
public int      query_allow_magic_attacks();
public int      query_reflect_damage_type();
public int      query_reflect_damage_combat_aid();
public int      query_reflect_damage_likelihood();

/*
 * Function:    config_reflect_spell
 * Description: Config function for reflect spells. Redefine this in your
 *              own reflect spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_reflect_spell()
{
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    // Set the effect object filename
    set_shadow_filename(STD_SPELL_OBJ_DIR + "reflect_sh");
    
    // Configure the spell parameters
    set_allow_specials(0);
    set_allow_magic_attacks(0);
    set_excluded_target_hit_locations( ({ }) );
    set_reflect_damage_combat_aid(25);
    set_reflect_damage_type(MAGIC_DT);
    set_reflect_damage_likelihood(75);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
}

public nomask void
config_shadow_spell()
{
    ::config_shadow_spell();

    set_spell_name("reflect");
    set_spell_desc("Reflect damage");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_reflect_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_reflect_spell();
    
    // Call this after the config_reflect_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
    resolve_reflect_spell(caster, targets, resist, result);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the shadow spell object
    spell_input["allow_specials"] = query_allow_specials();
    spell_input["allow_magic_attacks"] = query_allow_magic_attacks();
    spell_input["excluded_hit_locations"] = g_excludedTargetHitLocations;
    spell_input["damage_type"] = query_reflect_damage_type();
    spell_input["combat_aid"] = query_reflect_damage_combat_aid();
    spell_input["likelihood"] = query_reflect_damage_likelihood();
}

/*
 * Function name: has_spell_object
 * Description:   Checks to see if the target already has the spell object
 */
public int 
has_spell_object(object target)
{
    if (target->has_reflect_shadow())
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    // The reflect spell cannot be cast if it is already in effect
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
    }
    
    return result;    
}

// Setters and Getters

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
 * Function:    set_reflect_damage_combat_aid
 * Description: Sets the combat aid that will be provided by this reflect
 *              damage effect.
 *              25% aid == 20% reflected damage.
 */
public void
set_reflect_damage_combat_aid(int nCombatAid)
{
    g_nCombatAid = max(1, min(100, nCombatAid));
}

/*
 * Function:    query_reflect_damage_combat_aid
 * Description: Returns the combat aid that this reflect damage effect will
 *              have.
 */
public int
query_reflect_damage_combat_aid()
{
    return g_nCombatAid;
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

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_reflect_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_reflect_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("You are already reflecting damage!\n");
    }
    else
    {
        caster->catch_msg("You are already maintaining the ability to allow " 
            + QTNAME(target) + " to reflect damage.\n");
    }
}

/*
 * Function:    query_reflect_ingredients
 * Description: This function defines what components are required for
 *              this reflect spell.
 */
public string *
query_reflect_ingredients(object caster)
{
    return ({ });
}
