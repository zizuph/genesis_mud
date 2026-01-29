/*
 * Truesight divination spell for SOHM
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "darkvision";

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
    set_spell_name("vistoma");
    set_spell_desc("True sight - divine the ethereal and see through darkness");

    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_DIVINATION, 60);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);

    set_ability_stats(STAT_WEIGHTING);

    // Can cast truevision on others
    set_spell_target(spell_target_one_present_living);

    // Set the effect object filename
    set_spell_object(SOHM_SPELL_OBJS + "truesight_obj");

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
    return SOHM_MANAGER->query_memorised_spell(player,"vistoma_memorised");
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

        caster_message = "You raise your head to the heavens and fall in " +
            "to a trance, whispering 'vis toma' as you call on the powers " +
            "to see through darkness into the ethereal realms.\n";
        watcher_message = QCTNAME(caster) + " raises " + 
            caster->query_possessive() + " head to the heavens and falls " +
            "in to a trance, whispering mysterious words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}


public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the true sight spell.\n");
}

/*
 * Function:    query_darkvision_ingredients
 * Description: This function defines what components are required for
 *              this dark vision spell.
 */
public string *
query_darkvision_ingredients(object caster)
{
    return ({"_vistoma_charge","_leftover_eye","_leftover_eye"});
}
