/*
 * General Blink Spell
 * 
 * This is a generic blink spell that should be used as the basis for all
 * blink spells under the Genesis Magic system created in 2009.
 *
 * The blink spell behaves like the Calian move behind ability. It allows
 * a caster to avoid direct tanking at random intervals.
 *
 * Created by Petros, February 2016
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_blink_spell(object caster, mixed * targets, int * resist, int result);
public string * query_blink_ingredients(object caster);
public float query_blink_interval();

/*
 * Function:    config_blink_spell
 * Description: Config function for blink spells. Redefine this in your
 *              own blink spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blink_spell()
{
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Set the effect object filename
    set_spell_object(STD_SPELL_OBJ_DIR + "blink_obj");
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

    set_spell_name("blink");
    set_spell_desc("Teleport behind allies during combat");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_blink_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
        
    // Call the specific configuration that is to be masked.
    config_blink_spell();
    
    // Call this after the config_blink_spell to ensure that
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
    resolve_blink_spell(caster, targets, resist, result);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
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
            make_spell_object(query_spell_object(), caster, remaining_targets, remaining_resists, result, query_blink_interval());    
        }
    }
    else
    {
        make_spell_object(query_spell_object(), caster, targets, resist, result, query_blink_interval());
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
        // The blink spell cannot be stacked.
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
 * Function:    resolve_blink_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_blink_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_blink_interval
 * Description: This is the value that will be passed to the blink spell object
 *              to set the frequency at which the blink will be checked.
 * Returns:     a float in seconds for the average frequency of triggering
 *              a blink action.
 */ 
public float
query_blink_interval()
{
    return 30.0; // set default blink interval to 30 seconds.
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("You are already blinking in and out of the material plane.\n");
    }
    else
    {
        caster->catch_msg("You are already maintaining the ability for " 
            + QTNAME(target) + "to blink in and out of the material plane.\n");
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
 * Function:    query_blink_ingredients
 * Description: This function defines what components are required for
 *              this blink spell.
 */
public string *
query_blink_ingredients(object caster)
{
    return ({ });
}
