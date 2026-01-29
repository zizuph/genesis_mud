/*
 * Gravity spell for SOHM
 *
 * Coded by Arman 2017.
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
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/featherweight";

/*
 * Function:    config_featherweight_spell
 * Description: Config function for featherweight spells. Redefine this in your
 *              own featherweight spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_featherweight_spell()
{
    set_spell_name("haddross");
    set_spell_desc("Gravity - burden an enemy with earthly forces");

    set_spell_element(SS_ELEMENT_EARTH,  50);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_can_be_renewed(0);

    set_spell_target(spell_target_one_other_present_living_or_enemy);
   
    set_spell_object(SOHM_SPELL_OBJS + "gravity_obj");

    // Set the weight factor - 80% less weight capacity
    set_weight_factor(20);

}

/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
{
    return ({ "breadroot", "tangleshoot" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"haddross_memorised");
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
            "words of magic that will transform the order of nature, burdening " +
            COMPOSITE_LIVE(targets)+ " with gravitational forces.\n";
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

    if (caster == targets[0])
    {
        caster->catch_tell("You cannot burden yourself with gravitational forces.\n");
        return 0;
    } 

    object *target;

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_sohm_dominate())))
    {   
        if (target[0]->query_sohm_active())
        {
           caster->catch_tell("A domination enchantment interferes with your spell, " +
            "causing it to fail.\n");
            return 0;
        }
    }

    object tar = targets[0];

    if("/d/Krynn/guilds/sohm/spells/gravity"->has_spell_object(tar))
    {
        caster->catch_tell("Your target is already burdened with gravitational " +
             "forces.\n");
	return 0; 
    }

    if(tar->query_has_sohm_curse_shadow())
    {
        caster->catch_tell("A curse of uncertainty upon your target interferes with " +
            "your spell, causing it to fail.\n");
        return 0;
    }

    if("/d/Krynn/guilds/sohm/spells/haste"->has_spell_object(caster))
    {
        caster->catch_tell("Your haste spell interferes with your ability " +
              "to cast the gravity spell.\n");
	return 0; 
    }
  
    return 1;
}

/*
 * Function:    resolve_featherweight_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_featherweight_spell(object caster, mixed * targets, int * resist, int result) 
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
        caster->catch_msg("You are already maintaining gravitational forces " 
            + "upon " + QTNAME(target) + ".\n");

}

/*
 * Function:    hook_renew_spell_object 
 * Description: Message to give when the spell is recast onto an already existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew the duration of the gravity spell!\n");
}