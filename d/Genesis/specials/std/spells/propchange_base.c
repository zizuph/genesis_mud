/*
 * Prop Change Base Spell
 *
 * This spell gets clones a shadow object when it is cast.
 * We use a shadow to override the props in an object
 * instead of altering it. Using a shadow is typically safer
 * because it can handle stacking from multiple effects well.
 * 
 * Most of the time, you should be able to simply:
 * - inherit from /d/Genesis/specials/std/spells/propchange_base
 * - override the hook_* functions
 * - Implement the function for setting the input parameters
 * 
 * For the spell effect shadow, simply:
 * - inherit from /d/Genesis/specials/sd/spells/obj/propchange_base_sh
 * - Override query_prop with your own definition. Use the input_parameters
 *   as necessary.
 * - Override the hook_* functions

 * Created by Petros, July 2016
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";

// Prototypes
public void resolve_propchange_spell(object caster, mixed* targets, int* resist, int result, mapping spell_input);
public void hook_describe_cast_propchange(object caster, object* targets);

/*
 * Function:    query_propchange_ingredients
 * Description: This function defines what components are required for
 *              this propchange spell.
 */
public string *
query_propchange_ingredients(object caster)
{
    return ({  });
}

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */
public void
config_propchange_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    
    // Set the effect shadow
    set_shadow_filename(STD_SPELL_OBJ_DIR + "propchange_base_sh");
}

public nomask void
config_shadow_spell()
{
    ::config_shadow_spell();

    set_spell_name("propchange");
    set_spell_desc("change prop");
    set_spell_ingredients(query_propchange_ingredients);

    // Call the specific configuration that is to be masked.
    config_propchange_spell();
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
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
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
    hook_describe_cast_propchange(caster, targets);

    set_input_parameters(caster, targets, resist, result, spell_input);
    
    resolve_propchange_spell(caster, targets, resist, result, spell_input);
}


// HOOKS TO BE DEFINED
/*
 * Function:    resolve_illfortunate_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_propchange_spell(object caster, mixed * targets, int * resist,
                           int result, mapping spell_input)
{
}

/*
 * Function:    hook_describe_cast_illfortunate
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_propchange(object caster, object* targets)
{
    caster->catch_tell("You cast a prop change spell upon " +
                       COMPOSITE_LIVE(targets) + ".\n");
    caster->tell_watcher(QCTNAME(caster) + " casts a prop change spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " already is under the prop change spell effects!\n");
}
