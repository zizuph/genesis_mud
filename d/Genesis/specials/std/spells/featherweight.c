/*
 * General Featherweight Spell
 * 
 * This is a generic featherweight spell that should be used as the basis for all
 * featherweight spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, May 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_featherweight_spell(object caster, mixed * targets, int * resist, int result);
public string * query_featherweight_ingredients(object caster);
public void set_weight_factor(int factor);
public int  get_weight_factor();

// Global Variables
public int  Weight_factor = 140; // defaults to 40% more weight capacity

/*
 * Function:    config_featherweight_spell
 * Description: Config function for featherweight spells. Redefine this in your
 *              own featherweight spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_featherweight_spell()
{
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    // Spell effect object
    set_spell_object(STD_SPELL_OBJ_DIR + "featherweight_obj");
    
    // Set the weight factor - defaults to 140
    set_weight_factor(140);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
}

public nomask void
config_spell()
{
    set_spell_name("featherweight");
    set_spell_desc("Lighten heavy loads");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_featherweight_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_featherweight_spell();
    
    // Call this after the config_featherweight_spell to ensure that
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
    resolve_featherweight_spell(caster, targets, resist, result);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    mapping spell_input = ([ ]);
    spell_input["weight_factor"] = get_weight_factor();
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
            make_spell_object(query_spell_object(), caster, remaining_targets, remaining_resists, result, spell_input);    
        }
    }
    else
    {
        make_spell_object(query_spell_object(), caster, targets, resist, result, spell_input);
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
        // The featherweight spell cannot be cast if it is already in effect
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
 * Function:    set_weight_factor
 * Description: Sets the weight factor to be used in granting more carrying capacity
 */
public void
set_weight_factor(int factor)
{
    Weight_factor = factor;
}

/*
 * Function:    get_weight_factor
 * Description: Returns the specified weight factor for this shadow
 */
public int
get_weight_factor()
{
    return Weight_factor;
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_featherweight_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_featherweight_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("Your load is already light as a feather!\n");
    }
    else
    {
        caster->catch_msg("You are already maintaining the ability to lighten " 
            + QTNAME(target) + "'s burdens.\n");
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
    write("You renew the duration of the effect!\n");
}

/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
{
    return ({ });
}
