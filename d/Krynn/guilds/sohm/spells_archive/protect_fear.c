/*
 * Protection from dragon fear spell for SOHM
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/protect_dragonfear";

/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */

public void
config_protect_dragonfear_spell()
{
    set_spell_name("trothdraconis");
    set_spell_desc("Protect from fear - an ancient dragon fear protection spell");

    set_spell_element(SS_ELEMENT_FIRE,  40);
    set_spell_form(SS_FORM_ABJURATION, 40);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
   
    set_shadow_filename(SOHM_SPELL_OBJS + "protect_fear_sh");

}

/*
 * Function:    query_protect_dragonfear_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_protect_dragonfear_ingredients(object caster)
{
    return ({"tooth","mint" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"trothdraconis_memorised");
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

        caster_message = "Your eyes narrow in concentration as you begin reciting " +
            "ancient words of magic, a ward of protection from dragon fear!\n";
        watcher_message = QCTNAME(caster) + " narrows " + caster->query_possessive() + 
              " eyes in concentration and begins reciting mystical words of magic.\n";
        
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
  
    return 1;
}

/*
 * Function:    hook_describe_cast_propchange
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */

public void
hook_describe_cast_propchange(object caster, object* targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You cast a dragon fear protection spell upon "
                + "yourself and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You cast a dragon fear protection spell " +
                  "upon yourself.\n");
        }
    }
    else
    {
        caster->catch_tell("You cast a dragon fear protection spell upon "
            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " casts a spell of protection.\n", ({ }) );
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    if(target == caster)
      caster->catch_msg("You are already protected from dragon fear!\n");
    else
      caster->catch_msg(QCTNAME(target) + " is already protected from " +
           "dragon fear!\n");
}