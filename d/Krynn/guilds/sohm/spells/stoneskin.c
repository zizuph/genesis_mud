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

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "stoneskin";

#include "sohm_spell_functions.h"

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

    set_spell_combat_aid(70.0);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
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

    if(query_maintained_defensive_caid_spells(caster, "greater"))
    {
        // Allow spell to be renewed
        if("/d/Krynn/guilds/sohm/spells/stoneskin"->has_spell_object(caster))
            return 1;

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

