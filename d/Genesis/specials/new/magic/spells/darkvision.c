/*
 * General see dark spell
 * 
 * This is a generic see darkness spell that should be used as the basis 
 * for all see darkness spells under the Genesis Magic system created in 
 * 2009.
 *
 * Created by Eowul, Oktober 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_darkvision_spell(object caster, mixed *targets, int *resist, int result);
public string *query_darkvision_ingredients(object caster);

/*
 * Function:    config_darkvision_spell
 * Description: Config function for darkvision spells. Redefine this in your
 *              own darkvision spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_darkvision_spell()
{
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

    set_spell_name("darkvision");
    set_spell_desc("See in darkness");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_darkvision_ingredients);
    set_spell_class(SPELL_CLASS_2);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);

    // This is what we charge for the spell.
    set_spell_maintained_combat_aid(20.0);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    // Set the effect object filename
    set_spell_object(SPELL_OBJ_DIR + "darkvision_obj");
        
    // Call the specific configuration that is to be masked.
    config_darkvision_spell();
    
    // Call this after the config_darkvision_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets  - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    resolve_darkvision_spell(caster, targets, resist, result);

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
            make_spell_object(query_spell_object(), caster, remaining_targets, remaining_resists, result);
        }
    }
    else
    {
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, targets, resist, result);
    }
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
        // The darkvision spell cannot be cast if it is already in effect
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

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_darkvision_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_darkvision_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining ability to see in darkness.\n");
}

/*
 * Function:    query_darkvision_ingredients
 * Description: This function defines what components are required for
 *              this dark vision spell.
 */
public string *
query_darkvision_ingredients(object caster)
{
    return ({ "black pearl" });
}
