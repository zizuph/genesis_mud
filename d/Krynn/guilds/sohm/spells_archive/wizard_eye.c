/*
 * A resistance detection spell for SOHM
 * Uses the detect alignment base.
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <flags.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/alignment";

/*
 * Function:    config_alignment_spell
 * Description: Config function for alignment spells. Redefine this in your
 *              own alignment spells to override the defaults.
 *
 * Arguments:   None
 * Returns:     None
 */

public void
config_alignment_spell()
{
    set_spell_name("thixsauriv");
    set_spell_desc("Wizard eye - divine the magical resistances of a creature");

    set_spell_element(SS_ELEMENT_WATER, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

}

/*
 * Function name: resolve_alignment_spell 
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed* targets  - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_alignment_spell(object caster, mixed* targets, int* resist, int result)
{
}

/**
 * Function name : hook_fail_target_not_present
 * Description   : Writes output to caster when the target is not present.
 * Arguments     : object caster - the person casting the alignment spell.
 *               : object target - the specified target of the alignment spell.
 */
 
public void
hook_fail_target_not_present(object caster, object target)
{
    caster->catch_tell("Your specified target is not here to divine resistances.\n");
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell, who to check the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{
    if (target->query_prop(MAGIC_I_RES_FIRE)) 
    {
        caster->catch_msg("You sense that " + QTNAME(target) + " is resistant to fire.\n");
    }
    else
    {
        caster->catch_msg("You sense that " + QTNAME(target) + " is evil.\n");
    }
    target->catch_msg("You notice an intensive stare from " + QTNAME(caster) + ".\n");
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"thixsauriv_memorised");
}


/*
 * Function:    hook_identify_describe_cast
 * Description: Mask this function to display messages for the preparation
 *              for the identification. This is different from the
 *              concentration message because it happens right before the
 *              player actually sees the identify message.
 */
public void
hook_identify_describe_cast(object caster, object target)
{    
    caster->catch_tell("You open your hands wide and slowly move them over " + 
        FO_COMPOSITE_ALL_DEAD(({ target }), caster) + " while chanting " +
        "'oden arcanis'.\n");
    object * who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " opens " + caster->query_possessive() + 
              " hands wide and slowly moves them over " + QCOMPDEAD +
                   " while chanting words of magic.\n");
 
}

/*
 * Function:    hook_identify_sucess
 * Description: Mask this function to change the description of when
 *              the object is successfully identified.
 */
public void
hook_identify_success(object caster, object target, string id_message, int result)
{
    if (!objectp(caster) || !objectp(target))
    {
        return;
    }
    caster->catch_tell(id_message);

}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

/* Allowing these spells to potentially be more widely used than just SoHM
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a Student of High Magic!\n");
        return 0;
    }
    
    if (SOHM_MANAGER->is_casting_banned(caster))
    {
        caster->catch_tell("You have been banned from casting "
            + "spells for breaking the rules.\n");
        return 0;
    }

*/

    object target = targets[0];

    if (IS_LIVING_OBJECT(target))
    {
        caster->catch_tell("You can only cast this spell on items, not " +
           "living creatures.\n");
        return 0;
    }
  
    return 1;
}

/*
 * Function:    query_identify_ingredients
 * Description: This function defines what components are required for
 *              this identify spell.
 */
public string *
query_identify_ingredients(object caster)
{
    return ({ "water" });
}