#pragma strict_types

#include "../morgulmage.h"
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

inherit "/d/Genesis/specials/std/spells/invisibility";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public string *query_invisibility_ingredients(object caster);

public void
config_invisibility_spell()
{
    set_spell_name("artirith");
    set_spell_desc("Enter the realm of shadows");
    
    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

    set_spell_can_be_renewed(1);

    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_element(SS_ELEMENT_AIR, 50);
    
    set_spell_task(TASK_HARD);
    set_spell_time_factor(&adjust_time_by_rank(1.5)); // 4s x 1.5 = 6s

	set_shadow_filename(MORGUL_SPELL_OBJ_DIR + "artirith_sh");

    set_spell_ingredients(query_invisibility_ingredients);

    set_morgul_rank(15);
}

public string *
query_invisibility_ingredients(object caster)
{
    return ({ "_lominen_charge" });
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_invisibility_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_invisibility_spell(object caster, mixed * targets, int * resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target) {
        caster->catch_msg("You are already in the realm of shadows!\n");
    } else {
        caster->catch_msg(QCTNAME(target) + " is already in the realm of shadows!\n");
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
    write("You extend your stay in the realm of shadows!\n");
}