/*  /d/Raumdor/common/beach/bountiful/spells/ring_truesight.c
 *
 *  Truesight spell for the magical ring atan
 *  /d/Raumdor/common/beach/bountiful/chest_rewards/sight_ring.c
 *
 *  Based on the truesignt divination spell for SOHM made by
 *  Arman 2016.
 *
 *  Nerull, 2021
 *
 */

#pragma strict_types
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
inherit "/d/Genesis/specials/std/spells/darkvision";


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
    set_spell_name("truesight");
    set_spell_desc("truesight");
    set_spell_element(SS_ELEMENT_AIR, 0);
    set_spell_form(SS_FORM_DIVINATION, 0);
    set_spell_task(TASK_SIMPLE);
    set_spell_time_factor(0.5);
    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0); 
    set_spell_offensive(0);
    // Can cast truevision on others
    set_spell_target(spell_target_one_present_living);
    // Set the effect object filename
    set_spell_object("/d/Raumdor/common/beach/bountiful/spells/ring_truesight_obj.c");
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
    
    return 1;
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
    caster_message = "You rub the thin gold ring with your thumb.\n";
        
    caster->catch_tell(caster_message);
   
    setuid();
    seteuid(getuid());    
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the truesight ability.\n");
}


public void
hook_already_active(object player)
{
    write("You have already activated the thin gold ring. Patience!\n");
}


/*
 * Function:    query_darkvision_ingredients
 * Description: This function defines what components are required for
 *              this dark vision spell.
 */
public string *
query_darkvision_ingredients(object caster)
{
    return ({ });
}