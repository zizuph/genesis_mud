#pragma strict_types

#include "../morgulmage.h"
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/darkvision";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

/*
 * Function:    config_darkvision_spell
 * Description: Config function for darkvision spells. Redefine this in your
 *              own darkvision spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_darkvision_spell()
{
    set_spell_name("mortirio");
    set_spell_desc("See in Darkness");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0); 
    set_spell_offensive(0);
    
    set_spell_can_be_renewed(1);

    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 10);

    set_spell_task(TASK_HARD);

    set_spell_object(MORGUL_SPELL_OBJ_DIR + "mortirio");

    // Primary use is to cast on team members
    set_spell_target(spell_target_one_present_living);

    set_morgul_rank(1);

    set_spell_time_factor(adjust_time_by_rank);
}

public string *
query_darkvision_ingredients(object caster)
{
    return ({ "black potato" });
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute) 
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result) return result;
    
    foreach (object target : targets)
    {
        if(target->has_undead_shadow()) 
        {
            caster->catch_tell("The undead have no need for this spell " +
                "to enhance their vision!\n");
            return 0;        
        }
    }
    
    return 1;
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already
 *              existing effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    object * message_targets = target + ({ });
    message_targets -= ({ caster });

    write("You resummon mortirio upon " + COMPOSITE_LIVE(message_targets) + 
        ".\n");
}