/*
 * General Shadow Spell
 * 
 * This is a generic shadow spell that should be used as the basis for all
 * shadow spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, March 2011
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";

// Global Variables
public string   Shadow_filename = SPELL_OBJ_DIR + "shadow_base_sh";

// Prototypes
public void resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input);
public string * query_shadow_ingredients(object caster);
public void set_shadow_filename(string filename);
public string query_shadow_filename();

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{   
    set_shadow_filename(SPELL_OBJ_DIR + "shadow_base_sh");
}

public void 
set_shadow_filename(string filename)
{
    Shadow_filename = filename;
}

public string query_shadow_filename()
{
    return Shadow_filename;
}

private nomask void
config_shadow_required_parameters()
{
    // Place required parameters here.
    set_spell_object(SPELL_OBJ_DIR + "shadow_obj");
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("shadow");
    set_spell_desc("Shadow target");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_shadow_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_shadow_spell();
    
    // Call this after the config_shadow_spell to ensure that
    // required parameters aren't overridden
    config_shadow_required_parameters();
}

/* 
 * Function:    get_existing_spell_objects
 * Description: Spells sometimes need to check if the target already
 *              has an existing spell object for the spell. This is
 *              to either prevent another from being cast, or to remove
 *              the existing ones, and renew the effect.
 */
public object *
get_shadow_spell_objects(object target)
{
    // query_spell_obj, even though is coded to return functcions and object
    // instances, we will for the magic system only use strings.
    mixed spell_object_file = query_spell_object();
    if (!stringp(spell_object_file))
    {
        return 0;
    }
    
    mixed effects = filter(target->query_magic_effects(),
                        &wildmatch(spell_object_file + "#*") @ file_name);
    effects = filter(effects, &operator(==)(query_shadow_filename()) @ &->query_shadow_filename());
    if (sizeof(effects))    
    {   
        return effects;
    }
    
    return 0;
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
    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    mapping spell_input = ([ "shadow_filename" : query_shadow_filename() ]);
    // Pass in the spell_input variable so spells can add additional inputs
    resolve_shadow_spell(caster, targets, resist, result, spell_input);

    if (query_spell_can_be_renewed())
    {
        mixed * renewed_targets = ({ });
        mixed * remaining_targets = ({ });
        int * remaining_resists = ({ });
        for (int index = 0; index < sizeof(targets); ++index)
        {
            object * existing_objs = get_shadow_spell_objects(targets[index]);
            if (sizeof(existing_objs))
            {
                existing_objs->renew_spell_duration();
                renewed_targets += ({ targets[index] });
            }
            else
            {
                remaining_targets += ({ targets[index] });
                remaining_resists += ({ resist[index] });
            }
        }
        if (sizeof(renewed_targets))
        {
            hook_renew_spell_object(caster, renewed_targets);
        }
        if (sizeof(remaining_targets))
        {
            make_spell_object(query_spell_object(), caster, remaining_targets, remaining_resists, result, spell_input);    
        }
    }
    else
    {
        make_spell_object(query_spell_object(), caster, targets, resist, result, spell_input);
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{
    return ({ });
}

/* We mask a bunch of functions to allow them to be used in inherited shadow
 * functions */
/*
 * Function:    set_spell_mana
 * Description: Sets the base mana cost for the spell. By making it
 *              private, it prevents all inherited spells from setting
 *              it.
 */
static void 
set_shadow_spell_mana(int mana)
{
    set_spell_mana(mana);
}

static void 
set_shadow_spell_time(int seconds)
{
    set_spell_time(seconds);
}

/* 
 * Function:    get_existing_spell_objects
 * Description: Spells sometimes need to check if the target already
 *              has an existing spell object for the spell. This is
 *              to either prevent another from being cast, or to remove
 *              the existing ones, and renew the effect.
 */

public object *
get_existing_spell_objects(object target)
{
    // Just use the shadow version of this
    return get_shadow_spell_objects(target);
}
