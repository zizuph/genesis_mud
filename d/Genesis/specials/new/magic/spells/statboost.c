/*
 * General Stat Boost Spell
 * 
 * This is a generic stat boost spell that should be used as the basis for 
 * all stat boost spells in the new Genesis Magic system.
 *
 * Created by Petros, December 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_statboost_spell(object caster, mixed * targets, int * resist, int result);
public void add_stat_boost(int stat_id, int combat_aid);
public void hook_describe_cast_statboost(object caster, object * targets);
 
// Global Variables
public mapping stat_boost_mapping = ([ ]);

/*
 * Function:    config_statboost_spell
 * Description: Config function for stat boost spells. Redefine this in your
 *              own stat boost spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_statboost_spell()
{
    set_spell_object(SPELL_OBJ_DIR + "statboost_obj");    
    
    add_stat_boost(SS_STR, 10);
    add_stat_boost(SS_CON, 10);
}

/*
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this stat boost spell.
 */
public string *
query_statboost_ingredients(object caster)
{
    return ({ });
}

private nomask void
config_required_parameters()
{
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("statboost");
    set_spell_desc("boost stats");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_statboost_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH, 10);
    set_spell_form(SS_FORM_ABJURATION, 10);
        
    // Call the specific configuration that is to be masked.
    config_statboost_spell();
    
    // Call this after the config_resistance_spell to ensure that
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
    
    if (!query_spell_can_be_renewed())
    {
        // The same stat boost spell cannot be stacked.
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

/*
 * Function:    add_stat_boost
 * Description: Adds an element to the stat boost mapping. Call this inside
 *              of config_statboost_spell in your own implementation to
 *              define what stat boosts this spell will give.
 */
public void 
add_stat_boost(int stat_id, int combat_aid)
{
    stat_boost_mapping[stat_id] = combat_aid;
}

/*
 * Function:    query_added_stat_boosts
 * Description: Used when making the spell object. This returns the
 *              list of stat boosts that this spell will provide.
 * Returns:     Mapping of the format: SS_* => combat aid
 */
public mapping
query_added_stat_boosts()
{
    return stat_boost_mapping;
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
    resolve_statboost_spell(caster, targets, resist, result);

    // Show the resistance spell being cast
    hook_describe_cast_statboost(caster, targets);
    if (query_spell_can_be_renewed())
    {
        mixed * renewed_targets = ({ });
        mixed * remaining_targets = ({ });
        int * remaining_resists = ({ });
        for (int index = 0; index < sizeof(targets); ++index)
        {
            object * existing_objs = get_existing_spell_objects(targets[index]);
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
            make_spell_object(query_spell_object(), caster, remaining_targets, remaining_resists, result, query_added_stat_boosts());    
        }
    }
    else
    {
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, targets, resist, result, query_added_stat_boosts());    
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_statboost_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_statboost_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    hook_describe_cast_statboost
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_statboost(object caster, object * targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You cast a stat boost spell upon yourself "
                + "and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You cast a stat boost spell upon yourself.\n");
        }
    }
    else
    {
        caster->catch_tell("You cast a stat boost spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " casts a stat boost spell.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster != target)
    {
        caster->catch_msg(QCTNAME(target) + " already has stat boosts!\n");
    }
    else
    {
        write("You already have stat boosts!\n");
    }    
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew the duration of the effect!\n");
}
