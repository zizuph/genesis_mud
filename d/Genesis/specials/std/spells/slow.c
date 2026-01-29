/*
 * General Slow Spell
 * 
 * This is a generic slow spell that should be used as the basis for all
 * slow spells in the new Genesis Magic system.
 *
 * Created by Petros, March 2010
 *
 * Modified at 2021-06-01 by Carnak:
 *  - Affixed the factoring.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_slow_spell(object caster, mixed * targets, int * resist, int result);
public void hook_describe_cast_slow(object caster, object * targets);
public void hook_slow_resisted(object caster, object * targets);
public void set_slow_interval(float interval);
public void query_slow_interval();
 
// Global Variables
public float    Slow_interval = 1.0;

/*
 * Function name:   disable_pvp_abilities
 * Description:     Created to enable the override of pvp abilities.
 * Arguments:       (object) actor
 * Returns:         (status) 1 - Abilities disabled
 *                           0 - Abilities enabled
 */
public nomask status
disable_pvp_abilities(object actor)
{
    return PVP_ABILITY_DISABLED;
} /* disable_pvp_abilities */

/*
 * Function:    config_slow_spell
 * Description: Config function for slow spells. Redefine this in your
 *              own slow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_slow_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_object(STD_SPELL_OBJ_DIR + "slow_obj");    
    
    // By default, set the slow interval to 1.0
    set_slow_interval(1.0);
}

/*
 * Function:    query_slow_ingredients
 * Description: This function defines what components are required for
 *              this slow spell.
 */
public string *
query_slow_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
    set_ability_hasted(0);
    set_spell_offensive(1);
    set_spell_time_factor(0.75); // Fixed value as per AoB requirements
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("slow");
    set_spell_desc("slow movement");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_slow_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_slow_spell();
    
    // Call this after the config_slow_spell to ensure that
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
        
    // The same slow spell cannot be stacked.
    foreach (object target : targets)
    {
        if (target->has_slow_shadow())
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
    }
    
    return result;    
}

/*
 * Function:    set_slow_interval
 * Description: Sets the interval at which the slow spell will allow
 *              movement.
 */
public void 
set_slow_interval(float interval)
{
    Slow_interval = interval;
}

/*
 * Function:    query_slow_interval
 * Description: Returns the interval at which the slow spell will allow
 *              movement.
 */
public float
query_slow_interval()
{
    return Slow_interval;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - slow percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_slow_spell(caster, targets, resist, result);

    // Show the slow spell being cast
    hook_describe_cast_slow(caster, targets);

    // We check resistance to make sure that people who have sufficient
    // magical resistance don't get affected by the spell.
    int * slowed_resist = ({ });
    mixed * targets_slowed = ({ });
    mixed * targets_resisted = ({ });
    for (int index = 0; index < sizeof(targets); ++index)
    {
        if (resist[index] > random(100))
        {
            targets_resisted += ({ targets[index] });
        }
        else
        {
            targets_slowed += ({ targets[index] });
            slowed_resist += ({ resist[index] });
        }
    }
    
    if (sizeof(targets_resisted))
    {
        hook_slow_resisted(caster, targets_resisted);
    }
    
    if (sizeof(targets_slowed))
    {
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, targets_slowed, slowed_resist, result, query_slow_interval());    
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_slow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_slow_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_describe_cast_slow
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_slow(object caster, object * targets)
{
    caster->catch_tell("You cast a slow spell upon "
        + COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a slow spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already slowed!\n");
}

/*
 * Function:    hook_slow_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_slow_resisted(object caster, object * targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " are "
        + "not affected by your spell.\n");
    targets->catch_msg("You shrug off an attempt by " + QTNAME(caster)
        + "to slow you down.\n");
    caster->tell_watcher(QCTNAME(caster) + " doesn't seem to succeed in "
        + "trying to slow " + COMPOSITE_LIVE(targets) + ".\n",
        ({ caster }) + targets);
}
