/*
 * General disarm spell
 * 
 * This is a generic disarm spell that should be used as the basis 
 * for all disarm spells under the Genesis Magic system.
 * The target is not actually forced to unwield - instead, they are
 * forced to lose a fraction of their swings based on the combat aid
 * used.
 *
 * Created by Zizuph, July 2022
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
public void     resolve_disarm_spell(object caster, mixed * targets, int * resist, int result);
public string*  query_disarm_ingredients(object caster);
public void     resolve_disarm_resisted(object caster, object target, int resist, int result);
public void     hook_describe_disarm(object caster, mixed * targets, int result);
public void     hook_no_weapons_wielded(object caster, object target);

/*
 * Function:    config_disarm_spell
 * Description: Config function for disarm spells. Redefine this in your
 *              own diisarm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_disarm_spell()
{
    // Set the effect object filename
    set_spell_object(SPELL_OBJ_DIR + "disarm_obj");
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

    set_spell_name("disarm");
    set_spell_desc("Disarm target");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_disarm_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
        
    // Call the specific configuration that is to be masked.
    config_disarm_spell();
    
    // Call this after the config_blind_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

// This assumes the standard AC-based resistance is applied.  If the
// resistance calculation is changed, this should be overridden.
public float get_default_spell_resistance()
{
    return F_AC_MOD(40);
}

public int get_best_wielded_attack_id(object target)
{
    int best_attack_id = 0;
    int best_attack_use = 0;
    foreach (int id : target->query_combat_object()->query_attack_id())
    {
        mixed* attack = target->query_combat_object()->query_attack(id);
        // This should not happen.
        if (sizeof(attack) <= 4)
            continue;
        if (!target->query_weapon(id))
            continue;
        if ((attack[3] > best_attack_use) ||
          (target->has_active_disable_effect(best_attack_id)
           && !target->has_active_disable_effect(id)))
        {
            best_attack_use = attack[3];
            best_attack_id = id;
        }
    }
    return best_attack_id;
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
    resolve_disarm_spell(caster, targets, resist, result);
    
    hook_describe_disarm(caster, targets, result);
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        int resistance = resist[index];
        // Check resistance to see if the spell is resisted
        if (objectp(target) && resistance && resistance > random(100))
        {
            resolve_disarm_resisted(caster, target, resistance, result);
            continue;
        }
    
        int best_attack_id = get_best_wielded_attack_id(target);
        
        if (!best_attack_id)
        {
            hook_no_weapons_wielded(caster, target);
            continue;
        }
    
        mapping input = ([ "tohit" : convert_task_to_hit(get_spell_task()),
                       "resistance" : get_default_spell_resistance(),
                       "attack_id" : best_attack_id,
                       "targets"   : sizeof(targets)  ]);
        
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
resolve_disarm_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(QCTNAME(target)+" resisted your spell.\n");
    target->catch_msg("You resisted " + QTNAME(caster)+"'s spell.\n");
}

// HOOKS TO BE DEFINED

public void
hook_describe_disarm(object caster, mixed * targets, int result)
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


public void
hook_no_weapons_wielded(object caster, object target)
{
    if (objectp(target))
    {
        caster->catch_msg(QCTNAME(target) + " has no weapons wielded!\n");
    }
}


/*
 * Function:    resolve_disarm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_disarm_spell(object caster, mixed * targets, int * resist, int result)
{

}

/*
 * Function:    query_blind_ingredients
 * Description: This function defines what components are required for
 *              this blind vision spell.
 */
public string *
query_disarm_ingredients(object caster)
{
    return ({ "glittering diamond" });
}
