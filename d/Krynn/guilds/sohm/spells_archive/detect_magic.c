/*
 * Detect magic cantrip for SOHM
 *
 * Created by Arman 2016 based on base detect_magic spell
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/detect_magic";

/*
 * Function:    config_detect_magic_spell
 * Description: Config function for detect_magic spells. Redefine this in your
 *              own detect_magic spells to override the defaults.
 */

public void
config_detect_magic_spell()
{
    set_spell_name("ickrakarcanis");
    set_spell_desc("Detect magic - divine if an item is magical");

    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_DIVINATION, 20);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

    // Can only cast on one object
    set_spell_target(spell_target_one_present_object);

}


/*
 * Function:    resolve_detect_magic_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_detect_magic_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_detect_magic_ingredients(object caster)
{
    return ({ });
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
    return SOHM_MANAGER->query_memorised_spell(player,"ickrakarcanis_memorised");
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;
    object target = targets[0];

        caster_message = "You open your hands wide and slowly move them over the " +
                         target->short()+ " while chanting 'ickrak arcanis'.\n";
        watcher_message = QCTNAME(caster) + " opens " + caster->query_possessive() + 
              " hands wide and slowly moves them over the " +target->short()+
              " while chanting words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

/*  Allowing these spells to potentially be more widely used than just SoHM
    
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
 * Function:    hook_detect_magic_nonliving_results
 * Description: Override this function to describe what a player should see
 *              when they are detecting magic on a nonliving object.
 */
public void
hook_detect_magic_nonliving_results(object caster, object target, mapping magical_properties)
{
    if (m_sizeof(magical_properties))
    {
        caster->catch_msg("The " + target->short() + " glows briefly with a faint blue aura, " +
             "indicating it has magical properties.\n");
        tell_room(environment(caster), "The " + target->short() + " glows briefly with a faint blue aura.\n", 
             ({ caster }), caster);
    }
    else
    {
        caster->catch_msg("You don't detect any magical properties on the " + target->short() + ".\n");
    }
}

/*
 * Function:    hook_detect_magic_resisted
 * Description: Override this to customize the tell spell descriptions.
 */

public void
hook_detect_magic_resisted(object caster, object target, int resistance)
{
    caster->catch_msg("The " + target->short() + " resists your attempt to detect "
        + "magic.\n");
}

/*
 * Function:    hook_detect_magic_cast
 * Description: Override this to customize the tell spell descriptions.
 */

public void
hook_detect_magic_cast(object caster)
{
}