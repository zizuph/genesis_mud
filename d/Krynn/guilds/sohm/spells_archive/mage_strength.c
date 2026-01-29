/*
 * Mage strength lesser spell for SOHM
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

inherit "/d/Genesis/specials/std/spells/unfinished/regen_mana";

/*
 * Function:    config_regen_mana_spell
 * Description: Config function for regeneration spells. Redefine this in your
 *              own regeneration spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_regen_mana_spell()
{
    set_spell_name("hewavers");
    set_spell_desc("Mage strength - a spell of mental and physical reinforcement");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_EARTH,  50);
    set_spell_form(SS_FORM_TRANSMUTATION, 50);
    set_spell_task(TASK_HARD);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast strength on themself
    set_spell_target(spell_target_caster);

    // 20 caid applied here for the mana regen, 
    // Further caid applied in the spell object for the strength boost (9 caid).
    set_spell_combat_aid(20.0);    
    set_spell_object(SOHM_SPELL_OBJS + "mage_strength_obj");
}

/*
 * Function:    resolve_regen_mana_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_regen_mana_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_regeneration_ingredients
 * Description: This function defines what components are required for
 *              this regeneration spell.
 */
public string *
query_regen_mana_ingredients(object caster)
{
    return ({ "_hewavers_charge" });
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
    return SOHM_MANAGER->query_memorised_spell(player,"hewavers_memorised");
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

    caster_message = "You begin a slow chant in time with the beating of your heart, " +
    "starting softly and progressively getting louder as you transmute mystical energy " +
    "into physical strength.\n";
    watcher_message = QCTNAME(caster) + " begins a slow chant that progressively gets louder " +
    "and faster.\n";

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

    if (targets[0] != caster
      || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
	caster->catch_tell("You can only cast mage strength on yourself!\n");
	return 0;
    }

    return 1;
}
