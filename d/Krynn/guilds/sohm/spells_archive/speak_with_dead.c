/*
 * ukrisrivek: Speak with dead spell - Arman 2016
 *
 */

#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/identify";

/*
 * Function:    config_identify_spell
 * Description: Config function for identify spells. Redefine this in your
 *              own identify spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_identify_spell()
{
    set_spell_name("ukrisrivek");
    set_spell_desc("Speak with dead - Divine the cause of a corpse's death");
    set_spell_element(SS_ELEMENT_EARTH, 9);
    set_spell_form(SS_FORM_DIVINATION, 10);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

    // Being a cantrip, this spell is notoriously unreliable unless you have
    // decent divination skills.
    set_spell_task(TASK_DIFFICULT);    
}

/*
 * Function:    query_identify_ingredients
 * Description: This function defines what components are required for
 *              this identify spell.
 */
public string *
query_identify_ingredients(object caster)
{
    return ({ "_leftover_skull" });
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
        caster->catch_tell("You have been banned from casting combat "
            + "spells for breaking the rules.\n");
        return 0;
    }
*/

    if (targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        caster->catch_tell("For the living dead this spell is ineffective. Try "+
           "conversing normally?\n");
        return 0;
    }

    if (!targets[0]->query_prop(CORPSE_S_RACE))
    {
        caster->catch_tell("You can only cast this spell on corpses.\n");
        return 0;
    }
  
    return 1;
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
    return SOHM_MANAGER->query_memorised_spell(player,"ukrisrivek_memorised");
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
    string target = targets[0]->short();

        caster_message = "You kneel down beside the " +target+ " and murmur "
            + "powerful words of magic, 'Ukris rivek!'\n";
        watcher_message = QCTNAME(caster) + " kneels down beside the " +target+ 
              " and murmurs mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}



public string get_id_info(object target, int* result)
{
     return target->query_prop(CORPSE_AS_KILLER)[1];
}

/*
 * Function:    is_valid_identify_target
 * Description: Called from target_identify_spell, a customized spell should
 *              mask this and add any restrictions (such as guild members)
 *              on top of the base restrictions in targetting.
 * Returns:     0/1 - not valid/valid target
 */
public int
is_valid_identify_target(object target)
{
    return 1;
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

   
    caster->catch_tell("You touch the " +target->short()+ ".\n");
    tell_room(environment(caster), QCTNAME(caster) + " touches the " +target->short()+ " " +
              "while trying to divine its secrets.\n", ({ caster }), caster);

}
/*
 * Function:    hook_identify_success
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
    caster->catch_tell("You divine that the " +target->short()+ " was slain by the "+id_message+".\n");
}
/*
 * Function:    hook_identify_failure
 * Description: Describes the failure to actually magically identify the
 *              object.
 */
public void
hook_identify_failure(object caster, object target)
{
    caster->catch_tell("You fail to divine the death of the " +target->short()+ ".\n");
}
