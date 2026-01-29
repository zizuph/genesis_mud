/*
 * Divine Wizards cantrip for SOHM (list SoHM members)
 *
 * Created by Arman 2016.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{
    set_spell_name("ehtahhewa");
    set_spell_desc("Divine magus - divine fellow students in the realms");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_WATER,  5);
    set_spell_form(SS_FORM_DIVINATION, 5);
    // Reduced mana and difficulty - essentially a cosmetic spell
    set_spell_mana(5);
    set_spell_task(TASK_SIMPLE);

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast on self
    set_spell_target(spell_target_caster);
   
    set_shadow_filename(SOHM_SPELL_OBJS + "divine_wizards_sh");
}


/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
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
    return SOHM_MANAGER->query_memorised_spell(player,"ehtahhewa_memorised");
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

        caster_message = "You close your eyes and send your senses out, detecting " +
              "your fellow magi in the realms.\n";
        watcher_message = QCTNAME(caster) + " closes " + caster->query_possessive() + 
              " eyes and falls in to a trance.\n";
        
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

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast divine wizards on yourself!\n");
        return 0;
    }
  
    return 1;
}