/*
 * Stoneskin Spell for SoHM
 *
 * Coded by Arman 2016.
 * 
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/stoneskin";

/*
 * Function:    config_stoneskin_spell
 * Description: Config function for stoneskin spells. Redefine this in your
 *              own stoneskin spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_stoneskin_spell()
{
    set_spell_name("edarmolik");
    set_spell_desc("Stoneskin - Transform your skin to be hard as stone");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_combat_aid(90.0);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_task(TASK_HARD);    

    // Can only cast stoneskin on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "stoneskin_obj");
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    // Cladina - a rare and valuable herb that increases CON
    return ({ "cladina" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(SOHM_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast stoneskin on yourself!\n");
        return 0;
    }

    /*  Can't cast spell if using another defensive spell with high C.aid   */

    if("/d/Krynn/guilds/sohm/spells/blur"->has_spell_object(caster))
    {
        caster->catch_tell("Your blur spell interferes with your ability " +
              "to cast the stoneskin spell.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(caster))
    {
        caster->catch_tell("Your magic shield spell interferes with your ability " +
              "to cast the stoneskin spell.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/greater_magic_shield"->has_spell_object(caster))
    {
        caster->catch_tell("Your greater magic shield spell interferes with your ability " +
              "to cast the stoneskin spell.\n");
	return 0; 
    }

    if("/d/Krynn/guilds/sohm/spells/portents_and_omens"->has_spell_object(caster))
    {
        caster->catch_tell("Your portents and omens spell interferes with your ability " +
              "to cast the stoneskin spell.\n");
	return 0; 
    }

    object * effects = caster->query_prop("_live_o_maintained_effects");
    string caster_name = caster->query_real_name();

    foreach (object effect : effects)
    {
        if (objectp(effect))
        {
           if (environment(effect)->query_prop("_sohm_retributive_ward_effect") == caster_name)
           {
                caster->catch_tell("The retributive ward you are maintaining interferes " +
                                   "with your ability to cast the stoneskin spell.\n");
                return 0;
           }
        }
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
    return SOHM_MANAGER->query_memorised_spell(player,"edarmolik_memorised");
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

        caster_message = "You point to the ground and recite powerful words of magic - " +
           "'Dar molik!' - drawing energy from your surrounds into your body...\n";
        watcher_message = QCTNAME(caster) + " points to the ground and " +
           "begins reciting mystical words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function:    resolve_stoneskin_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stoneskin_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your skin is already as hard as stone. Casting the spell again will have " +
          "no effect!\n");
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You need a cladina herb to transmute your skin to stone.\n");
}

