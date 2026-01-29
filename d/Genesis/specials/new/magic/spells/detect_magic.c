/*
 * General Detect Magic Spell
 * 
 * This is a generic detect magic spell that should be used as the basis 
 * for all detect magic spells under the Genesis Magic system created 
 * in 2009.
 *
 * The detect magic can be cast against a single object. The object will
 * be checked for magical properties. We will not support a generic detect
 * magic that can actually "sniff" out magical items without individual
 * casts.
 *
 * Created by Petros, April 2012
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public string * query_detect_magic_ingredients(object caster);
public mapping  get_magical_properties(object target);
public void     resolve_detect_magic_spell(object caster, mixed * targets, int * resist, int result);
public void     hook_detect_magic_cast(object caster);
public void     hook_detect_magic_living_results(object caster, object target, object * effects);
public void     hook_detect_magic_nonliving_results(object caster, object target, mapping magical_properties);
public void     hook_detect_magic_resisted(object caster, object target, int resistance);

/*
 * Function:    config_detect_magic_spell
 * Description: Config function for detect_magic spells. Redefine this in your
 *              own detect_magic spells to override the defaults.
 */
public void
config_detect_magic_spell()
{

}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("detect_magic");
    set_spell_desc("Detect magic in the vicinity");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_mana(30);
    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(0);
    set_spell_ingredients(query_detect_magic_ingredients);
    set_spell_target(spell_target_one_present_object);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_detect_magic_spell();
    
    // Call this after the config_detect_magic_spell to ensure that
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
    resolve_detect_magic_spell(caster, targets, resist, result);

    hook_detect_magic_cast(caster);
    
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        int resistance = resist[index];
        if (objectp(target) && resistance > random(100))
        {
            hook_detect_magic_resisted(caster, target, resistance);
            continue;
        }
        
        // Living things and non-living things get treated differently
        if (IS_LIVING_OBJECT(target))
        {
            // For living things, just check to see if they have any
            // magical effects on them. We don't check their armours
            // or weapons.
            object * effects = target->query_magic_effects();
            hook_detect_magic_living_results(caster, target, effects);
        }
        else
        {
            mapping magical_properties = get_magical_properties(target);
            hook_detect_magic_nonliving_results(caster, target, magical_properties);
        }
    }        
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_detect_magic_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_detect_magic_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_detect_magic_not_allowed
 * Description: Override to customize the message for when the current
 *              environment does not allow one to detect magic here.
 */
public void
hook_detect_magic_not_allowed(object caster, string target)
{
    caster->catch_tell("You find your ability to sense magic to be muted "
        + "here.\n");
}

/*
 * Function:    hook_detect_magic_cast
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_magic_cast(object caster)
{
    caster->catch_msg("You start detecting magic.\n");
}

/*
 * Function:    hook_detect_magic_resisted
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_detect_magic_resisted(object caster, object target, int resistance)
{
    caster->catch_msg(QCTNAME(target) + " resists your attempt to detect "
        + "magic.\n");
}

/*
 * Function:    hook_detect_magic_living_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a living being.
 */
public void
hook_detect_magic_living_results(object caster, object target, object * effects)
{
    if (sizeof(effects))
    {
        caster->catch_msg("You detect magical effects on " + QTNAME(target) + ".\n");
    }
    else
    {
        caster->catch_msg("You don't detect any magic on " + QTNAME(target) + ".\n");
    }
}

/*
 * Function:    hook_detect_magic_nonliving_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a nonliving object.
 */
public void
hook_detect_magic_nonliving_results(object caster, object target, mapping magical_properties)
{
    if (m_sizeof(magical_properties))
    {
        caster->catch_msg("You detect magical properties on " + target->short() + ".\n");
    }
    else
    {
        caster->catch_msg("You don't detect any magic on " + target->short() + ".\n");
    }
}

/*
 * Function:    query_detect_magic_ingredients
 * Description: This function defines what components are required for
 *              this detect_magic spell.
 */
public string *
query_detect_magic_ingredients(object caster)
{
    // By default, use the herb for awareness
    return ({ "kuko" });
}

/*
 * Function:    process_magical_properties
 * Description: Magic Descriptions for items are stored in an array
 *              of pairs. They're either listed with level of
 *              magical identification, then description, or vice
 *              versa. We will test for both.
 */
private mapping
process_magical_properties(object target, string property)
{
    mixed * info = target->query_prop(property);
    if (!sizeof(info))
    {
        return 0;
    }
    
    mapping magical_property = ([ ]);
    
    for (int i = 0; i < (sizeof(info) - 1); i += 2)
    {
        int level = 0;
        string desc = "";
        if (intp(info[i]))
    	{
            level = info[i];
            desc  = info[i + 1];
    	}
        else if (intp(info[i + 1]))
    	{
            level = info[i + 1];
            desc  = info[i];
    	}
        else
    	{
            break;
    	}

        magical_property[level] = desc;
    }
    
    return magical_property;    
}

/*
 * Function:    get_magical_properties
 * Description: Return a mapping describing the magical properties
 *              keyed by the difficulty level of identifying that
 *              particular description
 * Arguments:   object target - the item to check for magical properties
 *              (see MAGIC_AM_ID_INFO and MAGIC_AM_MAGIC)
 * Returns:     a mapping of all the information from MAGIC_AM_ID_INFO 
 *              and MAGIC_AM_MAGIC. This will be passed to the spell's
 *              hook function to display to the user as it sees fit.
 */
public mapping
get_magical_properties(object target)
{
    mapping magical_info = process_magical_properties(target, MAGIC_AM_ID_INFO);
    mapping magical_type = process_magical_properties(target, MAGIC_AM_MAGIC);
    
    mapping magical_properties = ([ ]);
    if (m_sizeof(magical_info))
    {
        magical_properties[MAGIC_AM_ID_INFO] = magical_info;
    }
    if (m_sizeof(magical_type))
    {
        magical_properties[MAGIC_AM_MAGIC] = magical_type;
    }
    
    if (!m_sizeof(magical_properties))
    {
        return 0;
    }
    
    return magical_properties;
}
