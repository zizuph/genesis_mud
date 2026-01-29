/*
 * General Restore (Cure Blindness) Spell
 * 
 * This is a generic restore spell that should be used as the basis 
 * for all restore spells under the Genesis Magic system created in
 * 2009. Restore spells remove blindness from someone.
 *
 * Created by Jaacar, September 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include <composite.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Global variables

// Prototypes
public void         resolve_restore_spell(object caster, mixed * targets, int * resist, int result);
public string *     query_restore_ingredients(object caster);
public void         hook_describe_restore_cast(object caster, object * targets);
public void         hook_no_restore_required(object caster, object target);
public void         hook_restore_unsuccessful(object caster, object target);
public void         hook_restore_successful(object caster, object target);

/*
 * Function:    config_restore_spell
 * Description: Config function for restore spells. Redefine this in your
 *              own restore spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_restore_spell()
{
    set_spell_vocal(1);
    set_spell_visual(0);
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

    set_spell_name("restore");
    set_spell_desc("Cure blindness");

    set_spell_mana(30);
    set_spell_task(TASK_HARD); // Power Level 3 uses TASK_HARD
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_restore_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_WATER, 10);
    set_spell_form(SS_FORM_ABJURATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_restore_spell();
    
    // Call this after the config_cleanse_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

public void
restore_sight(object caster, object target, int strength)
{
    object blind_object;
    
    blind_object = present("_blind_object_", target);
    
    if (blind_object)
    {
        blind_object->remove_object();
        hook_restore_successful(caster, target);
        return;        
    }
    
    blind_object = present("Ranger_Blind_Object", target);
    
    if (blind_object)
    {
        blind_object->can_see_again();
        hook_restore_successful(caster, target);
        return;
    }
    
    hook_no_restore_required(caster, target);
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
    resolve_restore_spell(caster, targets, resist, result);

    // Display the spell being cast
    hook_describe_restore_cast(caster, targets);
    
    foreach (object target : targets)
    {
        restore_sight(caster, target, result);
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
resolve_restore_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_cleanse_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_restore_ingredients(object caster)
{
    return ({ });
}

public void
hook_describe_restore_cast(object caster, object * targets)
{
    if (sizeof(targets) > 1)
    {
        caster->catch_tell("You attempt to restore sight to "
            + COMPOSITE_LIVE(targets) + ".\n");    
        targets->catch_msg(QCTNAME(caster) + " tries to restore your sight.\n");
        tell_room(environment(caster), QCTNAME(caster) + " tries to "
            + "restore sight to " + COMPOSITE_LIVE(targets) + ".\n",
            ({ caster }) + targets );
    }
    else
    {
        object target = targets[0];
        if (caster == target)
        {
            caster->catch_tell("You attempt to restore your own sight.\n");    
            tell_room(environment(caster), QCTNAME(caster) + " tries to "
                + "restore sight for " + caster->query_objective() + "self.\n",
                ({ caster }) );
        }
        else
        {
            caster->catch_msg("You attempt to restore sight to "
                + QTPNAME(target) + ".\n");    
            target->catch_msg(QCTNAME(caster) + " tries to restore your "
                + "sight.\n");
            tell_room(environment(caster), QCTNAME(caster) + " tries to "
                + "restore the sight of " + QTNAME(target) + ".\n",
                ({ caster, target }) );
        }
    }    
}

public void
hook_no_restore_required(object caster, object target)
{
    caster->catch_tell("The target is not blinded.\n");    
}

public void
hook_restore_unsuccessful(object caster, object target)
{
    caster->catch_msg("You fail to restore sight to "
        + QTPNAME(target) + ".\n");
}

public void
hook_restore_successful(object caster, object target)
{
    if (caster == target)
	{
		caster->catch_tell("You restore your own sight.\n");
	}
	else
	{
	    caster->catch_tell("You restore sight to "
	        + target->query_the_name(caster) + ".\n");
	    target->catch_msg(QCTNAME(caster) + " restores your "
	    	+ "sight.\n");
	}
}

