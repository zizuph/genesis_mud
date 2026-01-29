/*
 * General Gem Converting Spell
 * 
 * This is a generic gem converting spell that should be used as the
 * basis for all gem converting spells in the new Genesis Magic system.
 *
 * Created by Navarre, October 2010.
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include <language.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/spell";

#include "/d/Genesis/specials/std/spells/centralized_spell.h"

// Prototypes
public void resolve_convert_gem_spell(object caster, mixed *targets, int *resist, int result);
public void hook_describe_convert_success(object caster, object gem, object new_obj);
public void hook_describe_convert_no_valid_gems_precast(object caster);
public void hook_describe_convert_no_valid_gems_postcast(object caster);
public void hook_describe_non_gem_target(object caster);
public void hook_describe_fake_gem_target(object caster);

/*
 * Function:    config_convert_gem_spell
 * Description: Config function for convert_gem_spell. Redefine this in your
 *              own convert gem spells to override the defaults.
 */
public void
config_convert_gem_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
}

/*
 * Function:    query_convert_gem_ingredients
 * Description: This function defines what components are required for
 *              this convert gem spell.
 */
public string*
query_convert_gem_ingredients(object caster)
{
    return ({});
}

private nomask void
config_required_parameters()
{
    set_spell_stationary(1);
    set_spell_peaceful(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("convert");
    set_spell_desc("Convert Gem");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(6);
    set_spell_target(spell_target_one_present_object);
    set_spell_ingredients(query_convert_gem_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 15);
    set_spell_form(SS_FORM_TRANSMUTATION, 35);
        
    // Call the specific configuration that is to be masked.
    config_convert_gem_spell();
    
    // Call this after the config_convert_gem_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    is_valid_gem_for_spell
 * Description: This returns whether this particular gem is valid to
 *              be used to convert from. This should be masked to match
 *              what type of gems are valid to use for the conversion.
 *
 * Arguments: object obj - the object to check for validity.
 * Returns: integer, 0 for invalid, 1 for valid.
 */
public int
is_valid_gem_for_spell(object obj)
{
    if (!objectp(obj) || !obj->query_gem())
    {
        return 0;
    }
    return 1;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed *targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);

    if (!result)
    {
        return 0; // result is 0;
    }

    if (!targets[0]->id("gem"))
    {
        hook_describe_non_gem_target(caster);
        return 0;
    }

    if (!IS_HEAP_OBJECT(targets[0]))
    {
        hook_describe_fake_gem_target(caster);
    }
    
    if (!is_valid_gem_for_spell(targets[0]))
    {
        hook_describe_convert_no_valid_gems_precast(caster);
        return 0;
    }
    return result;    
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets  - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    resolve_convert_gem_spell(caster, targets, resist, result);

    setuid();
    seteuid(getuid());

    if (!targets[0] || !is_valid_gem_for_spell(targets[0]))
    {
        hook_describe_convert_no_valid_gems_postcast(caster);
        return;
    }
    
    object converted_obj = clone_object(STD_SPELL_OBJ_DIR + "converted_obj");
    converted_obj->move(caster, 1);
    
    targets[0]->reduce_heap_size(1);

    hook_describe_convert_success(caster, targets[0], converted_obj);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_convert_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 *
 * Arguments:   object caster   - the caster
 *              mixed *targets  - an array of targets
 *              int *resist     - resistance percentages corresponding to
 *                                each target
 *              int result      - how well the spell was cast
 */
public void
resolve_convert_gem_spell(object caster, mixed *targets, int *resist, int result)
{
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *)  The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    caster->catch_tell("You clench " +targets[0]->short()+" in your hand.\n");

    tell_room(environment(caster), QCTNAME(caster) + " clenches " +
              caster->query_possessive() + " hand tightly.\n", ({caster}));
}

/*
 * Function:    hook_describe_convert_success
 * Description: Mask this function to describe the message that occurs when
 *              the spell completes successfully and a gem is converted.
 */
public void
hook_describe_convert_success(object caster, object gem, object new_obj)
{
    tell_room(environment(caster), "A brilliant burst of light shines from the hand of " +
	                            QTNAME(caster) + " temporarily blinding you.\n", caster);

    caster->catch_msg("A brilliant burst of light shines from your hand as the " +
                      gem->singular_short() + " transforms into " +
                      LANG_ADDART(new_obj->short()) + ".\n");
}

/*
 * Function:    hook_describe_convert_no_valid_gems_precast
 * Description: Mask this function to describe the message that occurs when the
 *              caster doesn't find a valid gem. Called from check_valid_action
 */
public void
hook_describe_convert_no_valid_gems_precast(object caster)
{
    caster->catch_tell("You don't have a valid gem to perform this conversion.\n");
}

/*
 * Function:    hook_describe_convert_no_valid_gems_postcast
 * Description: Mask this function to describe the message that occurs when
 *              the caster completes the spell, but finds no valid gem
 *              for the conversion.
 */
public void
hook_describe_convert_no_valid_gems_postcast(object caster)
{
    caster->catch_tell("You realize much too late that you don't have a " +
                       "required gem to perform the conversion.\n");
}

public void
hook_describe_non_gem_target(object caster)
{
    caster->catch_tell("You can only target gems.\n");
}

public void
hook_describe_fake_gem_target(object caster)
{
    caster->catch_tell("You cannot convert fake gems.\n");
}
