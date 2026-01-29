/*
 * General blind spell
 * 
 * This is a generic blindness spell that should be used as the basis 
 * for all blindness spells under the Genesis Magic system.
 *
 * Created by Navarre, March 2010.
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

#define HIS(x) ((x)->query_possessive())
#define HIM(x) ((x)->query_objective())

// Prototypes
public void     resolve_blind_spell(object caster, mixed * targets, int * resist, int result);
public string*  query_blind_ingredients(object caster);
public void     resolve_spell_resisted(object caster, object target, int resist, int result);
public void     hook_describe_blind(object caster, mixed * targets, int result);

/*
 * Function:    config_blind_spell
 * Description: Config function for blind spells. Redefine this in your
 *              own blind spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_blind_spell()
{
    // Set the effect object filename
    set_spell_object(SPELL_OBJ_DIR + "blind_obj");
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

    set_spell_name("blind");
    set_spell_desc("Blind target");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(&target_one_other_present_living_or_unaffected_enemy(&not() @ has_caster_spell_object));
    set_spell_ingredients(query_blind_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_blind_spell();
    
    // Call this after the config_blind_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
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


// This assumes the standard AC-based resistance is applied.  If the
// resistance calculation is changed, this should be overridden.
public float get_default_spell_resistance()
{
    return F_AC_MOD(40);
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
    resolve_blind_spell(caster, targets, resist, result);
    
    hook_describe_blind(caster, targets, result);
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
    
        mapping input = ([ "tohit" : convert_task_to_hit(get_spell_task()),
                           "resistance" : get_default_spell_resistance(),
                           "targets" : sizeof(targets) ]);
        
        // The spell object is created and moved to the target. It will
        // do all the descriptions in the spell object.
        make_spell_object(query_spell_object(), caster, target, resistance, 
            result, input);
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
    
    // With the new system, the blind object will reject being added if
    // the spell is already in effect.
    //foreach (object target : targets)
    //{
    //    if (has_spell_object(target))
    //    {
    //        hook_already_has_spell_object(caster, target);
    //        return 0;
    //    }
    //}
    return result;    
}

// HOOKS TO BE DEFINED

public void
hook_describe_blind(object caster, mixed * targets, int result)
{
    caster->catch_msg("Your prayers being heard, you extend " +
		      "your hands towards "+ COMPOSITE_LIVE(targets) +
		      " and feel the energy shoot out from your " +
		      "hands.\n");
    targets->catch_msg(QCTNAME(caster) + " extends " + HIS(caster) +
			  " hands, energy shooting towards you.\n");
    tell_room(environment(caster), 
        QCTNAME(caster) + " extends " + HIS(caster) + 
	      " hands towards " + COMPOSITE_LIVE(targets) +
	      " causing a flash of energy to ignite between them.\n",
	      ({ caster }) + targets, caster);
}

/*
 * Function:    resolve_blind_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_blind_spell(object caster, mixed * targets, int * resist, int result)
{

}

// This was used before to block a spell from being started.  Instead, we
// let the player try, and the blind will fail to add itself since the old
// effect is still in play/cooldown.
//public void
//hook_already_has_spell_object(object caster, object target)
//{
//    if (objectp(target))
//    {
//        caster->catch_msg("But " + QTNAME(target) + " is already blinded!\n");
//    }
//}

/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind vision spell.
 */
public string *
query_blind_ingredients(object caster)
{
    return ({ "glittering diamond" });
}
