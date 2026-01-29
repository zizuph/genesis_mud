/*
 * General Cleanse Spell
 * 
 * This is a generic cleanse spell that should be used as the basis for all
 * cleanse spells under the Genesis Magic system created in 2009. Cleanse
 * spells remove poison from someone under the effects of a poison.
 *
 * Created by Petros, March 2010
 *
 * Altered to TASK_ROUTINE to reflect as an occupational Class 2 spell, 
 * Arman 2022
 * 2022-02 Upped casting time to 5 - Zizuph
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include <poison_types.h>
#include <composite.h>

#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Global variables
public int      Cleanse_all         = 0;

// Prototypes
public void         resolve_cleanse_spell(object caster, mixed * targets, int * resist, int result);
public string *     query_cleanse_ingredients(object caster);
public void         set_cleanse_all(int cleanse_all);
public int          query_cleanse_all();
public void         hook_describe_cleanse_cast(object caster, object * targets);
public void         hook_no_cleanseable_poisons(object caster, object target);
public void         hook_no_poisons_cleansed(object caster, object target);
public void         hook_all_poisons_cleansed(object caster, object target);
public void         hook_some_poisons_cleansed(object caster, object target);

/*
 * Function:    config_cleanse_spell
 * Description: Config function for cleanse spells. Redefine this in your
 *              own cleanse spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_cleanse_spell()
{

    // Cleanse specific options
    set_cleanse_all(0);
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

    set_spell_name("cleanse");
    set_spell_desc("Cleanse poisons");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE); 
    set_spell_time_factor(1.5);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_cleanse_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_combat_aid(100);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_WATER, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_cleanse_spell();
    
    // Call this after the config_cleanse_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}


/*
 * Function:    set_cleanse_all
 * Description: If set to a non-zero integer, it indicates that this spell
 *              should attempt to cleanse all the poisons in the target.
 *              The default is to cleanse one poison at a time.
 */
public void
set_cleanse_all(int cleanse_all)
{
    Cleanse_all = 1;
}

/*
 * Function:    query_cleanse_all
 * Description: Returns whether this spell will try to cleanse all poisons
 *              or whether it will stop after cleansing one.
 */
public int
query_cleanse_all()
{
    return Cleanse_all;
}

public void
cleanse_poison(object caster, object target, int strength)
{
    // Lets try double strength here until system is fixed.
    strength *= 2;
    
    object * all_poisons = FILTER_POISON_OBJECTS(all_inventory(target));
    object * cleanseable_poisons = filter(all_poisons, not @ &->query_no_cleanse());
    if (!sizeof(cleanseable_poisons))
    {
        hook_no_cleanseable_poisons(caster, target);
        return;
    }

    send_debug_message("cleanse_spell", caster->query_name()
                         + " casts cleanse of strength " + strength + ".");                         
    
    object * cured_poisons = ({ });
    foreach (object poison : cleanseable_poisons)
    {
        int success = poison->cure_poison(
                             ({ poison->query_poison_type(),
                                POISON_CURE_FATIGUE,
                                POISON_CURE_HP,
                                POISON_CURE_MANA,
                                POISON_CURE_STAT }), strength);
        if (!success)
        {
            continue;
        }
        
        // Reduce chance based on amount of poisons.
        strength -= random(poison->query_strength());
        strength = max(strength, 0);
        cured_poisons += ({ poison });                                
        if (!query_cleanse_all())
        {
            break;
        }
    }
    
    // Now send messages depending on what was cured or not.
    if (sizeof(cured_poisons) == sizeof(cleanseable_poisons))
    {
        hook_all_poisons_cleansed(caster, target);
    }
    else if (!sizeof(cured_poisons))
    {
        hook_no_poisons_cleansed(caster, target);
    }
    else
    {
        hook_some_poisons_cleansed(caster, target);
    }
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
    resolve_cleanse_spell(caster, targets, resist, result);

    // Display the spell being cast
    hook_describe_cleanse_cast(caster, targets);
    
    foreach (object target : targets)
    {
        cleanse_poison(caster, target, result);
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_cleanse_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_cleanse_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_cleanse_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_cleanse_ingredients(object caster)
{
    return ({ });
}

public void
hook_describe_cleanse_cast(object caster, object * targets)
{
    if (sizeof(targets) > 1)
    {
        caster->catch_tell("You attempt to neutralize the poison in "
            + COMPOSITE_LIVE(targets) + ".\n");    
        targets->catch_msg(QCTNAME(caster) + " tries to cleanse a poison "
            + "in your body.\n");
        tell_room(environment(caster), QCTNAME(caster) + " tries to "
            + "cleanse " + COMPOSITE_LIVE(targets) + " of poison.\n",
            ({ caster }) + targets );
    }
    else
    {
        object target = targets[0];
        if (caster == target)
        {
            caster->catch_tell("You attempt to neutralize the poison in "
                + "your body.\n");    
            tell_room(environment(caster), QCTNAME(caster) + " tries to "
                + "cleanse " + caster->query_objective() + "self of poison.\n",
                ({ caster }) );
        }
        else
        {
            caster->catch_msg("You attempt to neutralize the poison in "
                + QTPNAME(target) + " body.\n");    
            target->catch_msg(QCTNAME(caster) + " tries to cleanse a poison "
                + "in your body.\n");
            tell_room(environment(caster), QCTNAME(caster) + " tries to "
                + "cleanse " + QTNAME(target) + " of poison.\n",
                ({ caster, target }) );
        }
    }    
}

public void
hook_no_cleanseable_poisons(object caster, object target)
{
    caster->catch_tell("You find nothing to cleanse.\n");    
}

public void
hook_no_poisons_cleansed(object caster, object target)
{
    caster->catch_msg("You fail to cleanse any poisons from "
        + QTPNAME(target) + " body.\n");
}

public void
hook_all_poisons_cleansed(object caster, object target)
{
    caster->catch_tell("You successfully cleanse all poisons.\n");
    target->catch_msg(QCTNAME(caster) + " cures all of your poisons.\n");
}

public void
hook_some_poisons_cleansed(object caster, object target)
{
    caster->catch_tell("You manage to cleanse some poisons, but still "
        + "some remain.\n");
    target->catch_msg(QCTNAME(caster) + " cures some of your poisons, but "
        + "some still remain.\n");
}
