/*
 * General Invisibility Spell
 * 
 * This is a generic gem invisibility spell that should be used as base
 * for all the invisibility spells in the new Genesis Magic system.
 *
 * Created by Eowul, July 2010
 */

#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <formulas.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_invisibility_spell(object caster, mixed * targets, int * resist, int result);

/*
 * Function:    config_invisibility_spell
 * Description: Config function for invisibility spells. Redefine this in your
 *              own spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_invisibility_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_offensive(0);
    
    // Set the effect shadow
    set_shadow_filename(STD_SPELL_OBJ_DIR + "invisibility_sh");
}

/*
 * Function:    query_invisitibility_ingredients
 * Description: This function defines what components are required for
 *              this invisibility spell.
 */
public string *
query_invisitibility_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
    set_spell_stationary(1);
    set_spell_peaceful(1);
}

public nomask void
config_shadow_spell()
{
    ::config_shadow_spell();

    set_spell_name("invisibility");
    set_spell_desc("Become invisible");

    set_spell_mana(30);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_invisitibility_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ILLUSION, 10);
        
    // Call the specific configuration that is to be masked.
    config_invisibility_spell();
    
    // Call this after the config_invisibility_spell to ensure that
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
        // The same invisibility spell cannot be stacked.
        foreach (object target : targets)
        {
            if (target->has_invisibility_shadow())
            {
                hook_already_has_spell_object(caster, target);
                return 0;
            }
        }
    }
        
    return result;    
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
    resolve_invisibility_spell(caster, targets, resist, result);

}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_invisibility_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_invisibility_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function name: has_spell_object
 * Description:   Checks to see if the target already has the spell object
 */
public int 
has_spell_object(object target)
{
    if (target->has_invisibility_shadow())
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already invisible!\n");
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
