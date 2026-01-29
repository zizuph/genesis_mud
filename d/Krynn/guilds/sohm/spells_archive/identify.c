/*
 * Identify magic spell for SOHM
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

inherit "/d/Genesis/specials/std/spells/identify";

/*
 * Function:    config_identify_spell
 * Description: Config function for identify spells. Redefine this in your
 *              own identify spells to override the defaults.
 */

public void
config_identify_spell()
{
    set_spell_name("odenarcanis");
    set_spell_desc("Identify - divine the magical properties of an item");

    set_spell_element(SS_ELEMENT_WATER, 30);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

}

/*
 * Function:    resolve_identify_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_identify_spell(object caster, mixed * targets, int * resist, int result)
{
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
    return SOHM_MANAGER->query_memorised_spell(player,"odenarcanis_memorised");
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