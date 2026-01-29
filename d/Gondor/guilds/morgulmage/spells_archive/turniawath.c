#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

inherit "/d/Genesis/specials/std/spells/resistance";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public void hook_already_has_ringurth_spell_object(object caster, object target);

public void
config_resistance_spell()
{
    set_spell_name("turniawath");
    set_spell_desc("Protect yourself with the Shadow Shield");
    
    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_task(TASK_HARD);

    set_spell_object(MORGUL_SPELL_OBJ_DIR + "turniawath");    

    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_form(SS_FORM_ABJURATION, 20);
    
    set_spell_target(spell_target_caster);

    add_resistance(MAGIC_I_RES_ACID, 50);
    add_resistance(MAGIC_I_RES_COLD, 50);
    add_resistance(MAGIC_I_RES_FIRE, 50);
    add_resistance(MAGIC_I_RES_LIFE, 50);
    add_resistance(MAGIC_I_RES_AIR,  50);

    set_morgul_rank(16);

    set_spell_can_be_renewed(1);
    set_spell_time_factor(adjust_time_by_rank);
}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ "_berichelkh_charge" });
}

public int has_ringurth_spell_object(object target)
{
    return query_has_spell_effect(target, MORGUL_SPELL_OBJ_DIR + "ringurth");
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute) {
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result) return result;
    
    foreach (object target : targets)
    {
        if(has_ringurth_spell_object(target)) {
            hook_already_has_ringurth_spell_object(caster, target);
            return 0;        
        }
    }
    
    return 1;
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, int * resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

/*
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    caster->catch_tell("You clench your fists as flames erupt suddenly"
        + " along every inch of your flesh. With a rush, the flames travel"
        + " along your body and disappear into trails of smoke.\n");    
    can_see_caster(caster)->catch_msg(QCTNAME(caster) + " stiffens briefly "
        + "as flames erupt and rush along the surface of " 
        + caster->query_possessive() + " flesh, disappearing into trails of "
        + "smoke.\n", caster);
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your flesh does not change, having already been augmented by you"
        + " not long ago.\n");  
}

/*
 * Function:    hook_already_has_ringurth_spell_object
 * Description: Get's called when the target is already under the effects of ringurth
 *              and can thus not use turniawath.
 */
public void
hook_already_has_ringurth_spell_object(object caster, object target)
{
    write("The wind fence protects you from the flames, and your flesh"
        + " is not affected by the spell.\n"); 
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("Your already charred flesh tightens with a crackling hiss, "
        + "renewed in its strength.\n");
}