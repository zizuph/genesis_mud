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
#include "../local.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "reflect";

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
    set_spell_name("lreflect");
    set_spell_desc("Reflect physical damage back at a foe");

    set_spell_fail("The Ancestors do not hear your call.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_ABJURATION, 60);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);    

    set_spell_target(target_one_present_living);

    // Spell effect object
    set_spell_object(SPELLS + "obj/reflect_damage_obj");

    // Configure the spell parameters
    set_allow_specials(1);
    set_allow_white_attacks(1);
    set_allow_magic_attacks(0);
    set_excluded_target_hit_locations( ({ }) );
    // 80% of damage reflected
    set_reflect_damage_combat_aid(90);
    set_reflect_damage_type(MAGIC_DT);
    // 60% change of damage reflected
    set_reflect_damage_likelihood(60);
}

/*
 * Function:    query_reflect_ingredients
 * Description: This function defines what components are required for
 *              this reflect spell.
 */

public string *
query_reflect_ingredients(object caster)
{
    return ({ "" });
}
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
	return 0;
    }

    //  Can't cast spell if using another defensive spell with high C.aid
    if("/d/Krynn/guilds/sohm/spells/stoneskin"->has_spell_object(caster))
    {
	caster->catch_tell("Your stoneskin spell interferes with your ability " +
	  "to cast retributive ward.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(caster))
    {
	caster->catch_tell("Your magic shield spell interferes with your ability " +
	  "to cast retributive ward.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/portents_and_omens"->has_spell_object(caster))
    {
	caster->catch_tell("Your portents and omens spell interferes with your ability " +
	  "to cast retributive ward.\n");
	return 0; 
    }

/* Can cast with blur and adv magic shield
    if("/d/Krynn/guilds/sohm/spells/blur"->has_spell_object(caster))
    {
	caster->catch_tell("Your blur spell interferes with your ability " +
	  "to cast retributive ward.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(caster))
    {
	caster->catch_tell("Your greater magic shield spell interferes with your ability " +
	  "to cast retributive ward.\n");
	return 0; 
    }
*/

    object * effects = caster->query_prop("_live_o_maintained_effects");
    string caster_name = caster->query_real_name();

    foreach (object effect : effects)
    {
        if (objectp(effect))
        {
           if (environment(effect)->query_prop("_reflect_effect") == caster_name)
           {
                caster->catch_tell("You are already maintaining a retributive ward.\n");
                return 0;
           }
        }
    }

    return 1;
}

public int
query_spell_can_be_learned(object player)
{
    if (player->query_npc())
    {
	// npcs can always learn the spell.
	return 1;
    }
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
	    caster_message = "You concentrate deeply reaching out to your  " +
	    "ancestors. Hearing you, they envelop you within a protect shield.\n";
	    watcher_message = QCTNAME(caster) + " turns inward, eyes closing, " +
	    "before snapping open, warding " +HIM(caster)+ "self with protective "
        +"energies.\n";

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
