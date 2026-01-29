#pragma strict_types

#include "../morgulmage.h"
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/d/Genesis/specials/std/spells/stoneskin";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public void hook_already_has_turniawath_spell_object(object caster, object target);

public void
config_stoneskin_spell()
{
    set_spell_name("ringurth");
    set_spell_desc("Conjure a protective shroud of death");

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    
    set_spell_can_be_renewed(1);

    set_spell_element(SS_ELEMENT_DEATH, 37);
    set_spell_form(SS_FORM_ABJURATION, 35);

    set_spell_task(TASK_HARD);

    set_spell_combat_aid(80.0);

    set_spell_object(MORGUL_SPELL_OBJ_DIR + "ringurth");

    set_spell_target(spell_target_caster);

    set_morgul_rank(8);

    set_spell_time_factor(adjust_time_by_rank);
}

float query_spell_combat_aid_modifier() 
{
    return itof(query_spell_guild_strength());
}

public string *
query_stoneskin_ingredients(object caster)
{
    return ({ "_berichelkh_charge" });
}

public int has_turniawath_spell_object(object target)
{
    return query_has_spell_effect(target, MORGUL_SPELL_OBJ_DIR + "turniawath");
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute) {
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result) return result;
    
    foreach (object target : targets)
    {
        if(has_turniawath_spell_object(target)) {
            hook_already_has_turniawath_spell_object(caster, target);
            return 0;        
        }
    }
    
    return 1;
}

// HOOKS TO BE DEFINED
/*
 * Function:    resolve_stoneskin_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stoneskin_spell(object caster, mixed * targets, int * resist, int result)
{
    caster->catch_tell("With the power the Dark Lord has bestowed "
        + "upon you, you call the Chill of Death.\n");
    can_see_caster(caster)->catch_msg("Employing Dark Sorcery, "
        + QTNAME(caster) + " calls upon the Chill of Death.\n");

    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("But you are already protected by the Chill of Death!\n");
}


/*
 * Function:    hook_already_has_turniawath_spell_object
 * Description: Get's called when the target is already under the effects of 
 *              turniawath and can thus not use ringurth.
 */
public void
hook_already_has_turniawath_spell_object(object caster, object target)
{
    write("You are unable to call upon the Chill of Death while maintaining " +
        "Shadow Shield.\n");
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already
 *              existing effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You resummon the Chill of Death, enveloping yourself anew in"
        + " a cold, comforting shadow of continued protection.\n");
}