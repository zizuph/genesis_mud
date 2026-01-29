/*
 * General Resistance Spell
 * 
 * This is a generic resistance spell that should be used as the basis for all
 * resistance spells in the new Genesis Magic system.
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

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_resistance_spell(object caster, mixed * targets, int * resist, int result);
public void hook_describe_cast_resistance(object caster, object * targets);
public void add_resistance(string element_property, int combat_aid);
 
// Global Variables
public mapping resistance_aid = ([ ]);

/*
 * Function:    config_resistance_spell
 * Description: Config function for resistance spells. Redefine this in your
 *              own resistance spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_resistance_spell()
{
    set_spell_object(SPELL_OBJ_DIR + "resistance_obj");    
    
    // Some default values by setting 4 elements to 25% combat aid. 
    // Change this as needed
    add_resistance(MAGIC_I_RES_FIRE, 25);
    add_resistance(MAGIC_I_RES_WATER, 25);
    add_resistance(MAGIC_I_RES_AIR, 25);
    add_resistance(MAGIC_I_RES_EARTH, 25);
}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("resistance");
    set_spell_desc("magic resistance");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_resistance_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 10);
    set_spell_form(SS_FORM_ABJURATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_resistance_spell();
    
    // Call this after the config_resistance_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
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
    
    if (!query_spell_can_be_renewed())
    {
        // The same resistance spell cannot be stacked.
        foreach (object target : targets)
        {
            if (has_spell_object(target))
            {
                hook_already_has_spell_object(caster, target);
                return 0;
            }
        }
    }
    
    return result;    
}

/*
 * Function:    add_resistance
 * Description: Adds an element to the resistance mapping. Call this inside
 *              of config_resistance_spell in your own implementation to
 *              define what resistances this spell will have.
 */
public void 
add_resistance(string element_property, int combat_aid)
{
    resistance_aid[element_property] = combat_aid;
}

/*
 * Function:    query_added_resistances
 * Description: Used when making the spell object. This returns the
 *              list of resistances that this spell will support.
 * Returns:     Mapping of the format: MAGIC_I_RES_* => combat aid
 */
public mapping
query_added_resistances()
{
    return resistance_aid;
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
    resolve_resistance_spell(caster, targets, resist, result);

    // Show the resistance spell being cast
    hook_describe_cast_resistance(caster, targets);

    if (query_spell_can_be_renewed())
    {
        mixed * renewed_targets = ({ });
        mixed * remaining_targets = ({ });
        int * remaining_resists = ({ });
        for (int index = 0; index < sizeof(targets); ++index)
        {
            object * existing_objs = get_existing_spell_objects(targets[index]);
            if (sizeof(existing_objs))
            {
                existing_objs->renew_spell_duration();
                renewed_targets += ({ targets[index] });
            }
            else
            {
                remaining_targets += ({ targets[index] });
                remaining_resists += ({ resist[index] });
            }
        }
        if (sizeof(renewed_targets))
        {
            hook_renew_spell_object(caster, renewed_targets);
        }
        if (sizeof(remaining_targets))
        {
            make_spell_object(query_spell_object(), caster, remaining_targets, remaining_resists, result, query_added_resistances());    
        }
    }
    else
    {
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, targets, resist, result, query_added_resistances());    
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You cast a resistance spell upon yourself "
                + "and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You cast a resistance spell upon yourself.\n");
        }
    }
    else
    {
        caster->catch_tell("You cast a resistance spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " casts a resistance spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster != target)
    {
        caster->catch_msg(QCTNAME(target) + " already has that resistance!\n");
    }
    else
    {
        write("You already have that resistance!\n");
    }    
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew the effects of the resistance you are maintaining!\n");
}
