/*
 * General Detect Resistance Spell
 * 
 * This is a generic detect resistance spell that should be used as the basis 
 * for all detect resistance spells under the Genesis Magic system created 
 * in 2009. 
 *
 * The detect resistance can be cast against a single living. The living will
 * be checked for magical resistance. We will not support a generic detect
 * magic that can actually "sniff" out magical items without individual
 * casts. Think of this spell like a "appraise enemy" spell.
 *
 * Created by Petros, July 2016
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Global Variables
public int * all_resistance_types = ({ MAGIC_I_RES_MAGIC,
            MAGIC_I_RES_FIRE,
            MAGIC_I_RES_WATER,
            MAGIC_I_RES_AIR,
            MAGIC_I_RES_DEATH,
            MAGIC_I_RES_LIFE,
            MAGIC_I_RES_EARTH,
            MAGIC_I_RES_POISON,
            MAGIC_I_RES_ILLUSION,
            MAGIC_I_RES_IDENTIFY,
            MAGIC_I_RES_COLD,
            MAGIC_I_RES_ELECTRICITY,
            MAGIC_I_RES_ACID,
            });

// Prototypes
public string * query_detect_resistance_ingredients(object caster);
public void     resolve_detect_resistance_spell(object caster, mixed * targets, int * resist, int result);
public void     hook_detect_resistance_cast(object caster);
public void     hook_detect_resistance_success(object caster, object target, mapping resistances);
public void     hook_detect_resistance_resisted(object caster, object target, int resistance);

/*
 * Function:    config_detect_resistance_spell
 * Description: Config function for detect_resistance spells. Redefine this in your
 *              own detect_resistance spells to override the defaults.
 */
public void
config_detect_resistance_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("detect_resistance");
    set_spell_desc("Detect resistance on someone");

    set_spell_mana(30);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(0);
    set_spell_ingredients(query_detect_resistance_ingredients);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_detect_resistance_spell();
    
    // Call this after the config_detect_resistance_spell to ensure that
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
    resolve_detect_resistance_spell(caster, targets, resist, result);

    hook_detect_resistance_cast(caster);
    
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        int resistance = resist[index];
        if (objectp(target) && resistance > random(100))
        {
            hook_detect_resistance_resisted(caster, target, resistance);
            continue;
        }

        mapping resistances = ([ ]);
        foreach (string element : all_resistance_types)
        {
            int res = target->query_magic_res(element);
            if (element != MAGIC_I_RES_MAGIC)
            {
                res = combine_resistances(target, ({ element, MAGIC_I_RES_MAGIC }));
            }
            if (res == 0)
            {
                continue;
            }
            resistances[element] = res;
        }
        
        hook_detect_resistance_success(caster, target, resistances);
    }        
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_detect_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_detect_resistance_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_detect_resistance_cast
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_resistance_cast(object caster)
{
    caster->catch_msg("You start detecting resistance.\n");
}

/*
 * Function:    hook_detect_resistance_resisted
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_resistance_resisted(object caster, object target, int resistance)
{
    caster->catch_msg(QCTNAME(target) + " resists your attempt to detect "
        + "resistance.\n");
}

/*
 * Function:    hook_detect_resistance_living_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a living being.
 */
public void
hook_detect_resistance_success(object caster, object target, mapping resistances)
{
    // TODO: Add default messages
    caster->catch_msg(QCTNAME(target) + " has the following resistances:\n");
    foreach (string element, int resistance : resistances)
    {
        caster->catch_msg("   " + element + ": " + resistance + "\n");
    }
}

/*
 * Function:    query_detect_resistance_ingredients
 * Description: This function defines what components are required for
 *              this detect_resistance spell.
 */
public string *
query_detect_resistance_ingredients(object caster)
{
    // By default, use the herb for awareness
    return ({ "kuko" });
}
