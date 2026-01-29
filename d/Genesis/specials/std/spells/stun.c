/*
 * General Stun Spell
 * 
 * This is a generic stun spell that should be used as the basis for all
 * stun spells in the new Genesis Magic system.
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

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_stun_spell(object caster, mixed * targets, int * resist, int result);
public void hook_describe_cast_stun(object caster, object * targets);
public void hook_target_stun_resisted(object caster, object * targets);
public void hook_target_stun_succeeded(object caster, object * targets);
 
/*
 * Function:    config_stun_spell
 * Description: Config function for stun spells. Redefine this in your
 *              own stun spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stun_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(100.0);

    set_spell_object(STD_SPELL_OBJ_DIR + "stun_obj");    
}

/*
 * Function:    query_stun_ingredients
 * Description: This function defines what components are required for
 *              this stun spell.
 */
public string *
query_stun_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_offensive(1);    
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("stun");
    set_spell_desc("Stun an opponent");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_stun_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 25);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);
        
    // Call the specific configuration that is to be masked.
    config_stun_spell();
    
    // Call this after the config_stun_spell to ensure that
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
    resolve_stun_spell(caster, targets, resist, result);

    // Show the stun spell being cast
    hook_describe_cast_stun(caster, targets);

    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    float aid = query_spell_combat_aid(); // effect uses combat aid
    int duration = query_spell_power() / 7; // F_PENMOD(60,100) = 396 / 7 = 56 seconds
    // randomize it a bit
    duration = (duration / 2) + random(duration / 2) + random(duration / 2);
    
    send_debug_message("stun_spell", "Casting stun spell with combat aid of "
        + ftoi(aid) + " and duration of " + duration + " seconds.");
            
    object * target_resisted = ({ });
    object * target_stunned = ({ });
    object * stun_objects = ({ });
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        int resistance = resist[index];
        // Test to see if the stun passes the resistance of the target
        if (resistance > random(100))
        {
            target_resisted += ({ target });
            continue;
        }

        target_stunned += ({ target });
        
        object stun_object = clone_object(query_spell_object());
        stun_object->set_stun_combat_aid(ftoi(aid));
        stun_object->set_stun_cycle_time(duration);
        stun_object->set_effect_caster(caster);
        stun_object->set_effect_target(target);
        stun_object->move(target, 1);
        stun_objects += ({ stun_object });
    }
    
    hook_target_stun_resisted(caster, target_resisted);
    hook_target_stun_succeeded(caster, target_stunned);        
    
    // Now start all the stun objects
    stun_objects->start();
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
        // The stun spell cannot be cast if it is already in effect
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
 * Function:    resolve_stun_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stun_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_describe_cast_stun
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_stun(object caster, object * targets)
{
    caster->catch_tell("You cast a stun spell toward " 
        + COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a stun spell.\n", ({ }) );
}

/*
 * Function:    hook_target_stun_resisted
 * Description: Called to show the messages of the targets that were not
 *              stunned because they resisted the spell.
 */
public void
hook_target_stun_resisted(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("You try to stun " + COMPOSITE_LIVE(targets) + ", but "
        + "your stun spell is resisted.\n");
    targets->catch_tell("You resist the stun spell.\n"); 
}

/*
 * Function:    hook_target_stun_succeeded
 * Description: Called to show the messages of the targets that were
 *              affected by the stun. Part of the stun messages
 *              will also be described by the stun object itself. Note
 *              that it's entirely possible the stun spell may hit,
 *              but because of a cooldown period, the stun may not
 *              actually have any effect.
 */
public void
hook_target_stun_succeeded(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("You hit " + COMPOSITE_LIVE(targets) + " with your "
        + "stun spell.\n");
    targets->catch_tell("You are struck by a stun spell.\n");
}
