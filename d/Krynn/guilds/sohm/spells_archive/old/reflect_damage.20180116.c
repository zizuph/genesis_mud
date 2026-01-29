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
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/reflect";

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

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_ABJURATION, 60);
    set_spell_task(TASK_HARD);    

    // Can only cast reflect on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_shadow_filename(SOHM_SPELL_OBJS + "reflect_damage_sh");

    // Configure the spell parameters
    set_allow_specials(1);
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
    return ({ "chicory","sphagnum" });
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
        caster->catch_tell("You can only cast retributive ward on " +
           "yourself!\n");
        return 0;
    }

    /*  Can't cast spell if using another defensive spell with high C.aid   */

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
    string caster_message, watcher_message;

        caster_message = "You recite powerful words of magic, and the ground beneath " +
           "you throbs with protective energy as you prepare to ward yourself.\n";
        watcher_message = QCTNAME(caster) + " recites mystical words of magic, " +
           "warding " +HIM(caster)+ "self with protective energies.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already maintaining the retributive ward. Casting the spell " +
          "again will have no effect!\n");
}
