/*
 * Turn Undead Spell - Arman, September 2017
 *
 * Based on blind base spell and Elementalist spell created by Jaacar, March 2017
 */

#pragma strict_types
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <composite.h>
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/new/magic/spells/centralized_spell_restrictions.h"

#define HIS(x) ((x)->query_possessive())
#define HIM(x) ((x)->query_objective())

// Prototypes
public void     resolve_turn_undead_spell(object caster, mixed * targets, int * resist, int result);
public string*  query_turn_undead_ingredients(object caster);
public void     resolve_spell_resisted(object caster, object target, int resist, int result);
public void     hook_describe_turn_undead(object caster, mixed * targets, int result);
public void     hook_maintaining_turn_undead(object caster, object target);
public void     hook_target_not_undead(object caster, object target);

/*
 * Function:    config_turn_undead_spell
 * Description: Config function for turn undead spells. Redefine this in your
 *              own turn undead spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_turn_undead_spell()
{  
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_object(SPELL_OBJ_DIR + "turn_undead_obj");        
} 

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_offensive(1);
}

public nomask void
config_spell()
{
    ::config_spell();
    set_spell_name("turn");
    set_spell_desc("Turn undead");
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_turn_undead_ingredients);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_ABJURATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_turn_undead_spell();
    
    // Call this after the config_turn_undead_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed* targets, int* resist, int result)
{
    resolve_turn_undead_spell(caster, targets, resist, result);
    
    hook_describe_turn_undead(caster, targets, result);
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        int resistance = resist[index];
        // Check resistance to see if the spell is resisted
        if (objectp(target) && resistance && resistance > random(100))
        {
            resolve_spell_resisted(caster, target, resistance, result);
            continue;
        }
    
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, target, resistance, result);
    }
}

/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing specific methods.
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your spell.\n");
    target->catch_msg("You resisted " + QTNAME(caster)+"'s spell.\n");
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

    if(caster->query_turn_undead_caster_shadow())
    {
        hook_maintaining_turn_undead(caster, targets[0]);
        return 0;
    }
    
    // The turn undead spell cannot be cast if it is already in effect. At some
    // point, if this spell is going to be mass cast, we should allow the
    // spell to be cast even if some of the targets have the turn undead spell on.
    // We just need to be careful not to stack the effects.
    foreach (object target : targets)
    {
        if (has_spell_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }

        if (!target->query_prop(LIVE_I_UNDEAD))
        {
            hook_target_not_undead(caster, target);
            return 0;
        }  
    }
    return result;    
}

// HOOKS TO BE DEFINED

public void
hook_describe_turn_undead(object caster, mixed * targets, int result)
{
    caster->catch_msg("Blazing light explodes from your raised hands, " +
        "forcing " +COMPOSITE_LIVE(targets) +" away from you through " +
        "a radiant intervention.\n");
    targets->catch_msg("Blazing light explodes from " +QTPNAME(caster) + 
        " raised hands, forcing you backwards as the " +
        "radiant intervention of a holy being works against " +
        "your undead form.\n");
    tell_room(environment(caster), "Blazing light explodes from " +QTPNAME(caster) +  
        " raised hands, forcing " + COMPOSITE_LIVE(targets) +
        " away through the radiant intervention of a holy being!\n",
        ({ caster }) + targets, caster); 
}

/*
 * Function:    resolve_turn_undead_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_turn_undead_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has already been turned!\n");
    }
}

public void
hook_maintaining_turn_undead(object caster, object target)
{
    caster->catch_msg("You are currently maintaining a spell of turn undead.\n");
}

public void
hook_target_not_undead(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " isn't undead!\n");
    }
}

/*
 * Function:    query_turn_undead_ingredients
 * Description: This function defines what components are required for
 *              this turn undead spell.
 */
public string *
query_turn_undead_ingredients(object caster)
{
    return ({ "holy water" });
}
