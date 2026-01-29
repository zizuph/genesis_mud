/*
 * General Shapeshift Spell
 * 
 * This is a generic shapeshift spell that should be used as the basis for all
 * shape shifting spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, May 2012
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";
inherit "/d/Sparkle/area/city/lib/utility_functions";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define OBJ_I_SHAPESHIFT_TARGET "_obj_i_shapeshift_target"

// Prototypes
public  void    resolve_shapeshift_spell(object caster, mixed * targets, int * resist, int result);
public void     hook_shapeshift_complete(object caster, object *targets);
public void     hook_invalid_shape_specified(object actor, string str);

// Global Variables
public mapping  shape_mapping = ([
    "mouse" : "/d/Genesis/race/shapeshift/mouse",
]);

/*
 * Function:    config_shapeshift_spell
 * Description: Config function for shapeshift spells. Redefine this in your
 *              own shapeshift spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shapeshift_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

    // Spell effect object
    set_spell_object(STD_SPELL_OBJ_DIR + "shapeshift_obj");
}

/* 
 * Function:    set_shape_mapping
 * Description: Sets the actual mapping that will be used to resolve the
 *              form based on the input that the caster passes as an
 *              argument.
 */
public void
set_shape_mapping(mapping shapes)
{
    shape_mapping = shapes + ([ ]);
}

/*
 * Function:    query_shape_mapping
 * Description: Allows the caller to fetch the actual mapping that is
 *              currently active.
 */
public mapping
query_shape_mapping()
{
    return shape_mapping;
}

/*
 * Function:    query_shapeshift_ingredients
 * Description: This function defines what components are required for
 *              this shapeshift spell.
 */
public string *
query_shapeshift_ingredients(object caster)
{
    // Onyx gem provides the "earth" element.
    return ({ "onyx" });
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

    set_spell_name("shapeshift");
    set_spell_desc("Change shape to something else");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_shapeshift_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 25);
    set_spell_form(SS_FORM_TRANSMUTATION, 25);
        
    // Call the specific configuration that is to be masked.
    config_shapeshift_spell();
    
    // Call this after the config_shapeshift_spell to ensure that
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
    resolve_shapeshift_spell(caster, targets, resist, result);

    // Get the currently set shape
    string target_shape_file = caster->query_prop(OBJ_I_SHAPESHIFT_TARGET);
    // Set up the input to the spell object
    mapping input = ([ ]);
    input["shape_file"] = target_shape_file;
    input["shapeshift_spell"] = this_object();
    // Make the spell object, which does the bulk of the work to actually do
    // the shapeshifting
    make_spell_object(query_spell_object(), caster, targets, resist, result, input);

    hook_shapeshift_complete(caster, targets);
    
    // Remove the shapeshift properties so it won't "dirty" the next cast
    targets->remove_prop(OBJ_I_SHAPESHIFT_TARGET);
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

    arg = lower_case(arg);
    string target_shape_file = shape_mapping[arg];
    setuid();
    seteuid(getuid());
    if (!strlen(target_shape_file)
        || !objectp(safely_load_master_file(target_shape_file)))
    {
        // First check if the master file can be loaded.
        hook_invalid_shape_specified(caster, arg);
        return 0;
    }
    
    // Add the property to the caster to keep track of which shape they
    // are planning on shifting into.
    caster->add_prop(OBJ_I_SHAPESHIFT_TARGET, target_shape_file);
    
    // The shapeshift spell cannot be cast if it is already in effect
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
 * Function:    resolve_shapeshift_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shapeshift_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already shape shifted!\n");
}

/*
 * Function name: hook_shapeshift_complete
 * Description  : Function called after the shapeshifting has been completed. 
 *              : Allows for messages to be written to the caster if he was
 *              : not the target of the shapeshift
 * Arguments    : caster - the caster
 *              : targets - the targets that got shapeshifted
 */
public void 
hook_shapeshift_complete(object caster, object *targets) 
{
}


/*
 * Function:    hook_invalid_shape_specified
 * Description: Called when the user specifies an invalid shape name. The
 *              shapes should be specified in the shape_mapping.
 */
public void 
hook_invalid_shape_specified(object actor, string str) 
{
    if (!strlen(str))
    {
        actor->catch_tell("You need to specify a form that you wish to "
            + "transform into.\n");
        return;
    }
    actor->catch_tell("You cannot transform to a " + str + ".\n");
}

/*
 * Function:    hook_cannot_clone_shape
 * Description: For some reason, cannot actually clone the shape. We
 *              should let the player know to contact a wizard.
 */
public void 
hook_cannot_clone_shape(object actor, string str) 
{
    actor->catch_tell("There is a permission "
        + "problem with your shapeshift spell and you cannot "
        + "transform into a " + str + ". Please contact a "
        + "wizard.\n");
}
