/*
 * General see invisible spell
 * 
 * This is a generic truesight spell that should be used as the basis 
 * for all truesight spells under the Genesis Magic system created in 
 * 2009.
 *
 * Created by Navarre, October 2010
 * Adapted by Petros, August 2012
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
public void resolve_truesight_spell(object caster, mixed *targets, int *resist, int result);
public string *query_truesight_ingredients(object caster);

/*
 * Function:    config_truesight_spell
 * Description: Config function for see invisible spells. Redefine this in your
 *              own see invisible spells to override the defaults.
 */
public void
config_truesight_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    // Set the effect object filename
    set_spell_object(STD_SPELL_OBJ_DIR + "truesight_obj");
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

    set_spell_name("truesight");
    set_spell_desc("Perceive the invisible");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_truesight_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE,  45);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
        
    // Call the specific configuration that is to be masked.
    config_truesight_spell();
    
    // Call this after the config_truesight_spell to ensure that
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
    resolve_truesight_spell(caster, targets, resist, result);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    make_spell_object(query_spell_object(), caster, targets, resist, result);
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed *targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    // The truesight spell cannot be cast if it is already in effect
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
 * Function:    resolve_truesight_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_truesight_spell(object caster, mixed *targets, int *resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining ability to see the invisible.\n");
}

/*
 * Function:    query_truesight_ingredients
 * Description: This function defines what components are required for
 *              this see the invisible spell.
 */
public string *
query_truesight_ingredients(object caster)
{
    return ({ "onyx" });
}
