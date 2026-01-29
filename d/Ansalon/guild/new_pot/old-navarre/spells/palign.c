/*
 * Palign spell for the Priests of Takhisis of Ansalon.
 * 
 * This spell reveals the alignment of a target player to the caster.
 *
 * Created by Navarre, March 6th, 2013.
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/alignment";

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include "/d/Ansalon/guild/new_pot/std/generic_functions.c"
#include "../defs.h"
#include <filter_funs.h>
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
    set_spell_name("palign");
    set_spell_desc("Detect someone's alignment");
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_DEATH, 10);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
}

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 2;
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
    caster->catch_tell("There is noone to focus your sight on.\n");
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
    string align_desc;
    
    if (target_alignment < -750)
    {
        align_desc = "midnight black";
    }
    else if (target_alignment < -400)
    {
        align_desc = "black";
    }
    else if (target_alignment < -100)
    {
        align_desc = "dark grey";
    }
    else if (target_alignment < 100)
    {
        align_desc = "grey";
    }
    else if (target_alignment < 400)
    {
        align_desc = "light grey";
    }
    else if (target_alignment < 750)
    {
        align_desc = "white";
    }
    else
    {
        align_desc = "pure white";
    }
    
    caster->catch_tell("You focus your sight above and beyond " +
                       target->query_the_name(caster) + ", and for a short " +
                       "while you can faintly detect a " + align_desc +
                       " aura.\n");
     // Tell only to people in the room that can see the caster.
    my_tell_roombb(environment(caster), QCTNAME(caster) + " seems to look " +
                "intently at something just behind " + QTNAME(target) + ".\n",
                caster, ({target}));
 
    // If the target can see the caster, which also includes being able to
    // see in the room he is in, then give him a message.
    if (CAN_SEE(target, caster) && CAN_SEE_IN_ROOM(target))
    {
        target->catch_tell(caster->query_The_name(target) + " seems to " +
                           "look intently at something just behind you.\n");
    }

    // Fallorn and potentially other PoT npcs cast spells such as this one
    // and this is a way to capture the results and have him act on it.
    if (caster->query_npc())
    {
        caster->cast_palign_hook(align_desc, target);
    }
}
/*
 * Function name : resolve_spell_resisted
 * Description   : The spell was resisted, this hook allows for writing
 *                 specific methods.
 *
 * Arguments     : object caster - The caster of the spell.
 *               : object target - The target of the spell.
 *               : int resist    - The resist value.
 *               : int result    - How well the spell was cast.
 */
public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_msg(caster->query_The_name(target) + " was unaffected by " +
                      " your prayer.\n");
    target->catch_msg(target->query_The_name(caster) + " recited your name " +
                      "in a prayer, but you feel unaffected.\n");
}


/*
 * Overriding resolve function to allow for spell adjustment based on 
 * spell cast result.
 *
 * Arguments:     object caster   - the caster
 *                mixed* targets  - an array of targets
 *                int* resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_alignment_spell(object caster,
                        mixed* targets,
                        int* resist,
                        int result)
{
    caster->adjust_standing_by_spell_level(query_spell_level(), result);    
}

/*
 * Function:    query_alignment_ingredients
 * Description: This function defines what components are required for
 *              this alignment spell.
 */
public string*
query_alignment_ingredients(object caster)
{
    return ({ "heart" });
}
