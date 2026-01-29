/*
 * This spell is based on the Priests of Takhisis curse spell called the
 * curse of the illfortunate. The main effect that this spell has is to
 * reduce the chances of the targeted person in successfully hitting his
 * targets. In this way, it is similar to an evade ability, except that
 * you cast it on someone else, which means that it affects all of the
 * target's enemies.
 * 
 * In order to use an ability like this, you must inherit from this
 * function in order to adhere to the Genesis Balance standards.
 *
 * Created by Navarre May 2013.
 * Adapted by Petros, July 2016
 * Modified:
 * - Removed the resist code and added set_spell_can_be_resisted which was
 *   just added to the centralized spell code.
 *   2018-01-26: Carnak
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit SPELL_DIR + "shadow";
#include "centralized_spell_restrictions.h"

// Prototypes
public int set_percentage_miss(int percentage); // convenience function to calculate the combat aid
public void resolve_illfortunate_spell(object caster, mixed* targets, int* resist, int result, mapping spell_input);
public void hook_describe_cast_illfortunate(object caster, object* targets);
public void hook_illfortunate_resisted(object caster, object* targets);

/*
 * Function:    config_illfortunate_spell
 * Description: Config function for illfortunate spell. Redefine this in your
 *              own illfortunate spells to override the defaults.
 */
public void
config_illfortunate_spell()
{   
    // Set the effect shadow
    set_shadow_filename(SPELL_OBJ_DIR + "illfortunate_sh");
    set_spell_combat_aid(15);
}

/*
 * Function:    query_illfortunate_ingredients
 * Description: This function defines the components to use for this spell.
 * Arguments:   The caster of this spell
 */
public string *
query_illfortunate_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
    set_spell_offensive(1);
}

public nomask void
config_shadow_spell()
{
    ::config_shadow_spell();

    set_spell_name("illfortunate");
    set_spell_desc("harder to hit");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(&target_one_other_present_living_or_unaffected_enemy(&not() @ has_caster_spell_object));
    set_spell_ingredients(query_illfortunate_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH,  20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);

    // Call the specific configuration that is to be masked.
    config_illfortunate_spell();
    
    // Added to be able to resist the code.
    set_spell_can_be_resisted(1);

    // Spell duration is set by the shadow, rather than the shadow
    // object.  In order to allow the shorter 30 second effect,
    // it is set when the shadow is initialized.  If the spell
    // object is renewed, that duration is lost.  This means we
    // need to block it from being renewable.
    set_spell_can_be_renewed(0);
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
    return result;    
}

/*
 * Function:    set_percentage_miss
 * Description: Sets the percentage of which the target should fail in 
 *              hitting his enemies. In reality, it will actually set
 *              the combat aid after taking into account the effect
 *              percentage to combat aid calculation.
 * Arguments:   percentage, the percentage to make the target miss with.
 */
public void
set_percentage_miss(int percentage)
{
    // Effect => Combat Aid Formula
    // (100 * effect_percentage) / (100 - effect_percentage)
    set_spell_combat_aid((100.0 * itof(percentage)) / (100.0 - itof(percentage)));
}

/*
 * Function:    attack_targets
 * Description: Called when using an offensive ability. Does the
 *              actual work of attacking each of the targets. Ensures
 *              that the fight actually begins.
 *              Override so that we don't switch targets for blind.
 *              Taken from Ckrik's work on plexus.
 */
public void
attack_targets(object actor, mixed * targets)
{
    attack_new_targets(actor, targets);
}


/*
 * Function:    query_percentage_miss
 * Description: Translates the combat aid back to the percentage miss
 *              calculation.
 */
public int
query_percentage_miss()
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
    hook_describe_cast_illfortunate(caster, targets);
    spell_input["percentage_miss"] = query_percentage_miss();
    resolve_illfortunate_spell(caster, targets, resist, result, spell_input);
}


// HOOKS TO BE DEFINED
/*
 * Function:    resolve_illfortunate_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_illfortunate_spell(object caster, mixed * targets, int * resist,
                           int result, mapping spell_input)
{
}

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_illfortunate(object caster, object* targets)
{
    caster->catch_tell("You cast a curse spell upon " +
                       COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a curse spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already cursed!\n");
}


/*
 * Function:    hook_curse_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets.
 */
public void
hook_illfortunate_resisted(object caster, object* targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " are " +
                      "not affected by your spell.\n");
    targets->catch_msg("You shrug off an attempt by " + QTNAME(caster) +
                       "to curse you.\n");
    caster->tell_watcher(QCTNAME(caster) + " doesn't seem to succeed in " +
                         "trying to curse " + COMPOSITE_LIVE(targets) + ".\n",
                         ({ caster }) + targets);
}

public void
hook_resist_spell_object(object *spell_objects, object caster, object *targets)
{
    // Added for backwards compatibility.
    hook_illfortunate_resisted(caster, targets);
}