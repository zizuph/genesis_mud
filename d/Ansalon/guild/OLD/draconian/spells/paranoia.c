/*
 * General paranoia spell
 * 
 * This is a generic implementation of a curse like spell that
 * gives paranoia to the target. Mainly there is a hook for
 * what effects should be displayed to the target as well as to
 * the people in the room with the target.
 *
 * Created by Navarre, October 2010.
 * Adapted by Petros, August 2012
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "/d/Genesis/specials/std/spells/defs.h"
#include "composite.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

#define HIS(x) ((x)->query_possessive())
#define HIM(x) ((x)->query_objective())

// Prototypes
public void resolve_paranoia_spell(object caster, mixed * targets, int * resist, int result);
public string* query_paranoia_ingredients(object caster);
public void resolve_spell_resisted(object caster, object target, int resist, int result);

/*
 * Function:    config_paranoia_spell
 * Description: Config function for paranoia spells. Redefine this in your
 *              own paranoia spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_paranoia_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);

    // Set the effect object filename
    set_spell_object(STD_SPELL_OBJ_DIR + "paranoia_obj");
}

private nomask void
config_required_parameters()
{
    set_spell_offensive(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("paranoia");
    set_spell_desc("Cause paranoia");

    set_spell_mana(10);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_paranoia_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE,  10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_paranoia_spell();
    
    // Call this after the config_paranoia_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed* targets, int* resist, int result)
{
    resolve_paranoia_spell(caster, targets, resist, result);

    // We only make them paranoia on success.
    if (result)
    {
        mixed * affected_targets = ({ });
        int * affected_resist = ({ });
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
                // Succeeded and was not resisted.
                affected_targets += ({ targets[index] });
                affected_resist += ({ resist[index] });
            }             
        }        
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, affected_targets, affected_resist, result);
    }
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your spell.\n");
    target->catch_msg("You resisted " + QTNAME(caster)+"'s spell.\n");
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
    
    // The paranoia spell cannot be cast if it is already in effect
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
 * Function:    resolve_paranoia_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_paranoia_spell(object caster, mixed * targets, int * resist, int result)
{
    if(result)
    {
        caster->catch_msg("Your prayers being heard, you extend " 
            + "your hands towards " + FO_COMPOSITE_ALL_LIVE(targets, caster)
            + " and feel the curse flow from your " 
            + "hands towards them.\n");
        targets->catch_msg(QCTNAME(caster) + " extends " + HIS(caster) 
            + " hands, a foul energy flowing inside you.\n");
        caster->tell_watcher(QCTNAME(caster) + " extends " + 
            caster->query_possessive() + " hands toward " +
            QCOMPLIVE + " causing a foul energy to flow between them.\n", 
            targets, ({ caster }) + targets);
    }
    else
    {
      caster->catch_tell("Your prayers remain unheard!\n");
    }
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (target)
    {
        caster->catch_msg("But "+QTNAME(target)+" is already paranoid!\n");
    }
}

/*
 * Function:    query_paranoia_ingredients
 * Description: This function defines what components are required for
 *              this paranoia vision spell.
 */
public string *
query_paranoia_ingredients(object caster)
{
    return ({ "eye" });
}
