/*
 * This silence spell is based on the illfortunate base spell.
 * 
 * In order to use an ability like this, you must inherit from this
 * function in order to adhere to the Genesis Balance standards.
 *
 * Created by Petros, July 2016
 * Adapted by Arman, Sep 2017
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "/d/Genesis/specials/std/spells/defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";
#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

#define SILENCE_SPELL_MOUTH_BLOCKED   ("_silence_spell_mouth_blocked")

// Prototypes
public int set_silence_duration(int percentage); // convenience function to calculate the combat aid
public void resolve_silence_spell(object caster, mixed* targets, int* resist, int result, mapping spell_input);
public void hook_describe_cast_silence(object caster, object* targets);
public void hook_silence_cooldown(object caster, object target);
public void hook_silence_resisted(object caster, object* targets);

/*
 * Function:    config_silence_spell
 * Description: Config function for silence spell. Redefine this in your
 *              own silence spells to override the defaults.
 */
public void
config_silence_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    
    // Set the effect shadow
    // set_shadow_filename(STD_SPELL_OBJ_DIR + "silence_sh");
    set_shadow_filename("/d/Genesis/specials/std/spells/unfinished/silence_sh");

    set_spell_combat_aid(50);
}

/*
 * Function:    query_silence_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments:   The caster of this spell
 */
public string *
query_silence_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_offensive(1);
}

public nomask void
config_shadow_spell()
{
    ::config_shadow_spell();

    set_spell_name("silence");
    set_spell_desc("silence the target");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_silence_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR,  20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);

    // Call the specific configuration that is to be masked.
    config_silence_spell();
    
    // Call this last to ensure that
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
        
    // We do not allow stacking of this spell
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
    }

    foreach (object target : targets)
    {
        if (target->query_prop(SILENCE_SPELL_MOUTH_BLOCKED) > time())
        {
            hook_silence_cooldown(caster, target);
            return 0;
        }
    }
    return result;    
}

/*
 * Function:    set_silence_duration
 * Description: Sets the percentage of time the silence is modified by
 *              depending on caid. In reality, it will actually set
 *              the combat aid after taking into account the effect
 *              percentage to combat aid calculation.
 * Arguments:   time, the percentage to make the target miss with.
 */
public void
set_silence_duration(int percentage)
{
    // Effect => Combat Aid Formula
    // (100 * effect_percentage) / (100 - effect_percentage)
    // 50% of time silenced equates to 100% combat aid.
    set_spell_combat_aid((100.0 * itof(percentage)) / (100.0 - itof(percentage)));
}

/*
 * Function:    query_silence_duration
 * Description: Translates the combat aid back to the duration
 *              calculation.
 */
public int
query_silence_duration()
{
    // Combat Aid => Effect formula
    // (100 * combat_aid) / (100 + combat_aid)
    float aid = query_spell_combat_aid();
    return ftoi((100.0 * aid) / (100.0 + aid));
}

/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public nomask void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
    // Show the spell being cast
    hook_describe_cast_silence(caster, targets);

    // People who resist the silence should suffer no effects from it.
    int * silence_resist = ({ });
    mixed * targets_cursed = ({ });
    mixed * targets_resisted = ({ });
    for (int index = 0; index < sizeof(targets); ++index)
    {
        if (resist[index] > random(100))
        {
            targets_resisted += ({ targets[index] });
        }
        else
        {
            targets_cursed += ({ targets[index] });
            silence_resist += ({ resist[index] });
        }
    }
    // Need to update the original input parameters so that resolve_spell in
    // parent shadow can properly create the right spell objects
    targets -= targets;
    targets += targets_cursed;
    resist -= resist;
    resist += silence_resist;
    
    if (sizeof(targets_resisted))
    {
        hook_silence_resisted(caster, targets_resisted);
    }

    spell_input["silence_duration"] = query_silence_duration();
    resolve_silence_spell(caster, targets, resist, result, spell_input);
}


// HOOKS TO BE DEFINED
/*
 * Function:    resolve_silence_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_silence_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
}

/*
 * Function:    hook_describe_cast_silence
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_silence(object caster, object* targets)
{
    caster->catch_tell("You cast a silence spell upon " +
                       COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a silence spell.\n", ({ }) );

    // 30 seconds before a silence spell can be cast on the target again
    foreach(object target: targets)
    {
        target->add_prop(SILENCE_SPELL_MOUTH_BLOCKED, time() + 30);
    }
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already silenced!\n");
}

/*
 * Function:    hook_silence_cooldown
 * Description: Function that gets called to tell the caster that the cooldown
 *              is in effect.
 */
public void
hook_silence_cooldown(object caster, object target)
{
    int wait_time = target->query_prop(SILENCE_SPELL_MOUTH_BLOCKED) - time();
    string seconds;

    if(wait_time > 60)
      seconds = "over a minute";
    else if(wait_time > 1)
      seconds = wait_time+ " seconds";
    else
      seconds = wait_time+ " second";

    caster->catch_msg(QCTNAME(target) + " was recently magically silenced. You " +
            "will need to wait " +seconds+ " before you can magically " +
            "silence " +target->query_objective()+ " again.\n");
}


/*
 * Function:    hook_silence_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_silence_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " has " +
                      "not been affected by your spell.\n");
    targets->catch_msg("You shrug off an attempt by " + QTNAME(caster) +
                       "to silence you.\n");
    caster->tell_watcher(QCTNAME(caster) + " doesn't seem to succeed in " +
                         "trying to silence " + COMPOSITE_LIVE(targets) + ".\n",
                         ({ caster }) + targets);
}
