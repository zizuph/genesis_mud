/*
 * General Delayed Trigger Spell
 * 
 * This is a generic delayed trigger spell that should be used as the basis for all
 * delayed spells under the Genesis Magic system created in 2009.
 * 
 * A delayed trigger spell is a spell that "hangs" in the air after it has been
 * successfully cast. It then waits for the trigger event. Once the trigger occurs,
 * then the spell is discharged.
 *
 * TODO: Still need to specify method of activating spell
 * 
 * Created by Petros, November 2012
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include "defs.h"

inherit SPELL_DIR + "shadow";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_delayedtrigger_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input);
public string * query_delayedtrigger_ingredients(object caster);

// Global Variables
public string   m_sTriggeredSpell = SPELL_DIR + "stoneskin"; // set stoneskin as a sample.

public void
set_triggered_spell(string filename)
{
    m_sTriggeredSpell = filename;
}

public string
query_triggered_spell()
{
    return m_sTriggeredSpell;
}

/*
 * Function:    config_delayedtrigger_spell
 * Description: Config function for delayedtrigger spells. Redefine this in your
 *              own delayedtrigger spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_delayedtrigger_spell()
{
    // Set the effect object filename
    set_shadow_filename(SPELL_OBJ_DIR + "delayedtrigger_sh");    
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

    set_spell_name("delayedtrigger");
    set_spell_desc("Delays the trigger of a spell");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_delayedtrigger_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_delayedtrigger_spell();
    
    // Call this after the config_delayedtrigger_spell to ensure that
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
    resolve_delayedtrigger_spell(caster, targets, resist, result, spell_input);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object. Add any additional
    // information to spell_input mapping
    spell_input["triggered spell"] = m_sTriggeredSpell;
    spell_input["caster"] = caster;
    spell_input["targets"] = targets;
    spell_input["resist"] = resist;
    spell_input["result"] = result;
}

/*
 * Function name: has_spell_object
 * Description:   Checks to see if the target already has the spell object
 */
public int 
has_spell_object(object target)
{
    if (target->has_delayedtrigger_shadow())
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
    
    // The delayedtrigger spell cannot be cast if it is already in effect
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

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_delayedtrigger_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_delayedtrigger_spell(object caster, mixed * targets, int * resist, int result, mapping spell_int)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("You already have a delayed trigger spell!\n");
    }
    else
    {
        caster->catch_msg(QCTNAME(target) + " already has a delayed trigger "
            + "spell.\n");
    }
}

/*
 * Function:    query_delayedtrigger_ingredients
 * Description: This function defines what components are required for
 *              this delayedtrigger spell.
 */
public string *
query_delayedtrigger_ingredients(object caster)
{
    return ({ });
}
