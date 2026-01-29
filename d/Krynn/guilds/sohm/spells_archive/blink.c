/*
 * Blink abjuration spell for SOHM
 * Created by Arman 2016, based on blink base code by Petros.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/blink";

/*
 * Function:    config_blink_spell
 * Description: Config function for blink spells. Redefine this in your
 *              own blink spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_blink_spell()
{
    set_spell_name("ripeidronik");
    set_spell_desc("Blink - phase shift behind a team member");

    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast blink on themself
    set_spell_target(spell_target_caster);

    // Set the effect object filename
    set_spell_object(SOHM_SPELL_OBJS + "blink_obj");

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
    return SOHM_MANAGER->query_memorised_spell(player,"ripeidronik_memorised");
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

        caster_message = "You rapidly trace a sygil of protection in the air while chanting " +
            "'Ripeidronik!'\n";
        watcher_message = QCTNAME(caster) + " rapidly traces a complicated sygil in the air " +
           "while chanting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}


public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("You are already blinking in and out of the material plane.\n");
    }
    else
    {
        caster->catch_msg("You are already maintaining the ability for " 
            + QTNAME(target) + "to blink in and out of the material plane.\n");
    }
}

/*
 * Function:    query_blink_ingredients
 * Description: This function defines what components are required for
 *              this blink spell.
 */
public string *
query_blink_ingredients(object caster)
{
    return ({ "hazelnut" });
}