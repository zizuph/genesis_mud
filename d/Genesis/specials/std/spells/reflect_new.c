/*
 * General reflect Spell
 * 
 * This is a generic reflect spell that should be used as the basis for all
 * reflect spells in the new Genesis Magic system.
 *
 * Created by Petros, March 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Global Variables
public int      g_bAllowSpecials = 0;
public int      g_bAllowMagicAttacks = 0;
public int      g_bAllowWhiteAttacks = 1;
public int *    g_TargetHitLocations = ({ });
public int *    g_TargetHitLocations = ({ });
public int      g_damageType = MAGIC_DT;
public int      g_nLikelihood = 75;

// Prototypes
public void     resolve_reflect_spell(object caster, mixed *targets,
                                      int *resist, int result);
public void     set_allow_specials(int bAllowSpecials);
public void     set_allow_magic_attacks(int bAllowMagicAttacks);
public void     set_allow_white_attacks(int bAllowWhiteAttacks);
public void     set_excluded_target_hit_locations(int *TargetHitLocations);
public void     set_reflect_damage_combat_aid(int nCombatAid);
public void     set_reflect_damage_type(int damageType);
public void     set_reflect_damage_likelihood(int likelihood);
public int      query_allow_specials();
public int      query_allow_magic_attacks();
public int      query_allow_white_attacks();
public int      query_reflect_damage_type();
public int      query_reflect_damage_combat_aid();
public int      query_reflect_damage_likelihood();
public int      query_allow_target_hitloc(int target_hitloc);

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
    // Configure the spell parameters
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

private nomask void
config_required_parameters()
{
    // Place required parameters here.
}

public nomask void
config_spell()
{
    ::config_spell();

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

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_allow_specials(0);
    set_allow_magic_attacks(0);
    set_allow_white_attacks(1);
    set_excluded_target_hit_locations( ({ }) );
    set_reflect_damage_combat_aid(25);
    set_reflect_damage_type(MAGIC_DT);
    set_reflect_damage_likelihood(75);

    set_spell_object(STD_SPELL_OBJ_DIR + "reflect_obj");
       
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
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_reflect_spell(caster, targets, resist, result);

    mapping spell_input = ([]);
    
    // The spell object is created and moved to the target. It will
    // do all the descriptions in the shadow spell object
    spell_input["allow_specials"] = query_allow_specials();
    spell_input["allow_magic_attacks"] = query_allow_magic_attacks();
    spell_input["allow_white_attacks"] = query_allow_white_attacks();
    spell_input["excluded_hit_locations"] = g_TargetHitLocations;
    spell_input["damage_type"] = query_reflect_damage_type();
    spell_input["combat_aid"] = query_reflect_damage_combat_aid();
    spell_input["likelihood"] = query_reflect_damage_likelihood();
    
    make_spell_object(query_spell_object(), caster, targets, resist, result, spell_input);
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
    set_spell_combat_aid(nCombatAid);
}

/*
 * Function:    query_reflect_damage_combat_aid
 * Description: Returns the combat aid that this reflect damage effect will
 *              have.
 */
public int
query_reflect_damage_combat_aid()
{
    return ftoi(query_spell_combat_aid());
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
 * Function:    set_allow_white_attacks
 * Description: Usually called in the initialize_shadow function. This sets
 *              whether the reflective damage will apply when the attack
 *              is a white hit, like a normal weapon hit.
 */
public void
set_allow_white_attacks(int bAllowWhiteAttacks)
{
    g_bAllowWhiteAttacks = bAllowWhiteAttacks;
}

/*
 * Function:    query_allow_white_attacks
 * Description: Returns whether reflective damage will apply when the attack
 *              is a white hit, like a normal weapon hit.
 */
public int
query_allow_white_attacks()
{
    return g_bAllowWhiteAttacks;
}

/*
 * Function:    set_excluded_target_hit_locations
 * Description: Sets up the locations that should not reflect damage. The
 *              argument is an integer array of the hit locations.
 */
public void      
set_excluded_target_hit_locations(int * TargetHitLocations)
{
    if (sizeof(TargetHitLocations))
    {
        g_TargetHitLocations = TargetHitLocations + ({ });
    }
    else
    {
        g_TargetHitLocations = ({ });
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
    return IN_ARRAY(target_hitloc, g_TargetHitLocations);
}

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