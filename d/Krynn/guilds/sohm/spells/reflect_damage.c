/*
 * Reflect damage spell for SoHM
 *
 * Coded by Arman 2016.
 * 
 * Based on code by Petros, September 2009
 */

#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include <wa_types.h>
#include <composite.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "reflect";

#include "sohm_spell_functions.h"

/*
 * Function:    config_reflect_spell
 * Description: Config function for reflect spells. Redefine this in your
 *              own reflect spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_reflect_spell()
{
    set_spell_name("viraxregpos");
    set_spell_desc("Retributive ward - Reflect physical damage back at a foe");

    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_ABJURATION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);    

    set_spell_target(target_one_present_living);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "reflect_damage_obj");

    // Configure the spell parameters
    set_allow_specials(1);
    set_allow_white_attacks(1);
    set_allow_magic_attacks(0);
    set_excluded_target_hit_locations( ({ }) );

    set_reflect_damage_combat_aid(70);
    set_reflect_damage_type(MAGIC_DT);
    // 100% change of damage reflected
    set_reflect_damage_likelihood(100);
}

/*
 * Function:    query_reflect_ingredients
 * Description: This function defines what components are required for
 *              this reflect spell.
 */

public string *
query_reflect_ingredients(object caster)
{
    return ({ "chicory","sphagnum" });
}
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
	return 0;
    }

    if(query_maintained_defensive_caid_spells(caster, "greater"))
    {
        // Allow for spell to be renewed.
        if(caster->query_prop("_sohm_retributive_ward_effect"))
        {
            return 1;
        }

	caster->catch_tell("You can only maintain one greater spell " +
           "that provides combat utility at a time.\n");
	return 0; 
    }

    return 1;
}

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
    return SOHM_MANAGER->query_memorised_spell(player,"viraxregpos_memorised");
}
// HOOKS TO BE DEFINED

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
    string caster_message, watcher_message, target_message;
    object target = targets[0];

    object * message_targets = targets + ({ });
    message_targets -= ({ caster });

    if (IN_ARRAY(caster, targets))
    {
	if (!sizeof(message_targets))
	{
	    caster_message = "You recite powerful words of magic, and the ground beneath " +
	    "you throbs with protective energy as you prepare to ward yourself.\n";
	    watcher_message = QCTNAME(caster) + " recites mystical words of magic, " +
	    "warding " +HIM(caster)+ "self with protective energies.\n";

	    caster->catch_tell(caster_message);
	    tell_room(environment(caster), watcher_message, ({ caster }), caster);
	}
    }
    else
    {
	caster_message = "You recite powerful words of magic, and the ground beneath " +
	"you throbs with protective energy as you prepare to ward " +
	COMPOSITE_LIVE(message_targets)+ ".\n";
	target_message = QCTNAME(caster) + " recites mystical words of magic, " +
	"warding you with protective energies.\n";
	watcher_message = QCTNAME(caster) + " recites mystical words of magic, " +
	"warding " +COMPOSITE_LIVE(message_targets)+ " with protective energies.\n";

	caster->catch_msg(caster_message);
	targets->catch_msg(target_message);
	caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);
    }

    setuid();
    seteuid(getuid());    
}
