/*
 * General alignment checking spell
 * 
 * This is a generic alignment checking spell that should be used as the basis 
 * for all alignment checking spells under the Genesis Magic system.
 *
 * Created by Navarre, September 2010.
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
public void resolve_alignment_spell(object caster,
                                    mixed * targets,
                                    int * resist,
                                    int result);

public string* query_alignment_ingredients(object caster);

public void resolve_spell_resisted(object caster,
                                   object target,
                                   int resist,
                                   int result);

public void hook_fail_target_not_present(object caster, object target);

public void hook_report_alignment(object caster,
                                  object target,
                                  int target_alignment,
                                  int result);

/*
 * Function:    config_alignment_spell
 * Description: Config function for alignment spells. Redefine this in your
 *              own alignment spells to override the defaults.
 *
 * Arguments:   None
 * Returns:     None
 */
public void
config_alignment_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
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

    set_spell_name("alignment");
    set_spell_desc("Check target's alignment");

    set_spell_mana(30);
    set_spell_task(TASK_EASY);
    set_spell_time(3);
    set_spell_target(spell_target_one_other_present_living);
    set_spell_ingredients(query_alignment_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_alignment_spell();
    
    // Call this after the config_alignment_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets  - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed* targets, int* resist, int result)
{
    // Allows implementer of specific alignment spells to add more
    // logic for resolving the spell.
    resolve_alignment_spell(caster, targets, resist, result);

    // We only detect their alignment on success.
    if (result)
    {
        int num_targets = sizeof(targets);
        for (int index = 0; index < num_targets; ++index)
        {
            if (!objectp(targets[index]))
            {
                continue;
            }
            
            // Check if the spell was resisted
            if (resist[index] && random(100) < resist[index])
            {
                resolve_spell_resisted(caster, targets[index], resist[index], result);
            }
            else
            {
                // Succeeded and was not resisted. We call the hook method now to
                // get the alignment and display it properly.
                int alignment = targets[index]->query_alignment();
                hook_report_alignment(caster, targets[index], alignment, result);
            }             
        }
    }
}

/*
 * Function name: resolve_alignment_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets  - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_alignment_spell(object caster, mixed* targets, int* resist, int result)
{
  // Overriding this function can let the implementer of an alignment spell
  // Specify more logic that he wants checked before the resolve_spell logic occurs.
}

/**
 * Function name : hook_fail_target_not_present
 * Description   : Writes output to caster when the target is not present.
 * Arguments     : object caster - the person casting the alignment spell.
 *               : object target - the specified target of the alignment spell.
 */
public void
hook_fail_target_not_present(object caster, object target)
{
    caster->catch_tell("Your specified target is not here to check for alignment.\n");
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell, who to check the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{
    if (target_alignment > 0)
    {
        caster->catch_msg("You sense that " + QTNAME(target) + " is good.\n");
    }
    else
    {
        caster->catch_msg("You sense that " + QTNAME(target) + " is evil.\n");
    }
    target->catch_msg("You notice an intensive stare from " + QTNAME(caster) + ".\n");
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing
 *                 specific methods.
 *
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target) + " resisted your spell.\n");
    target->catch_msg("You resisted " + QTNAME(caster) + "'s spell.\n");
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed *targets, string arg, int execute)
{
    // We can take this function out if we dont need to add anything special.
    return ::check_valid_action(caster, targets, arg, execute);
}

// HOOKS TO BE DEFINED

/*
 * Function:    query_alignment_ingredients
 * Description: This function defines what components are required for
 *              this alignment spell.
 */
public string *
query_alignment_ingredients(object caster)
{
    return ({ "eye" });
}
