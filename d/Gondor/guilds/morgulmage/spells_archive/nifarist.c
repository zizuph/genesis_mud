/*
 * Nifarist makes someone forget who you are.
 * 
 * Created by Eowul, November 2013
 */
 
#pragma strict_types

#include "../morgulmage.h"
#include <options.h>
#include <macros.h>
#include <flags.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>

inherit "/d/Genesis/specials/std/spells/shadow";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public string *query_nifarist_ingredients(object caster);

public void 
config_shadow_spell()
{
    set_spell_name("nifarist");
    set_spell_desc("Withdraw into your robe, hiding your identity");
    
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_ABJURATION, 20);

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);  

    set_spell_task(TASK_ROUTINE);
    
    set_spell_target(spell_target_caster);

    set_spell_ingredients(query_nifarist_ingredients);

    set_shadow_filename(MORGUL_SPELL_OBJ_DIR + "nifarist_sh");
    set_morgul_rank(18);

    set_spell_can_be_renewed(1);
    set_spell_time_factor(adjust_time_by_rank);
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
        return result;
    }

    object robe = present(MORGUL_S_SPELL_OBJECT, caster);
    if (!objectp(robe) || (robe->query_worn() != caster)) 
    {
        caster->catch_tell("You are not wearing your robe!\n");
        return 0;
    }

    if (!caster->query_hooded())
    {
        caster->catch_tell("You are not wearing your hood!\n");
        return 0;
    }

    return result;
}

public string *
query_nifarist_ingredients(object caster)
{
    return ({ "_mapa_charge" });
}


public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_SMALL_SPELL); 
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already
 *              existing effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You pull your robe closely about you, feeling the shadows of"
      + " Mordor concealing your identity anew.\n");
}
