/*
 * A magic shield for SoHM, based on the stoneskin spell 
 *
 * Coded by Arman 2016.
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
    set_spell_name("arcanfethos");
    set_spell_desc("Magic shield - A shield of magic force that absorbs damage");

    set_spell_combat_aid(30.0);

    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_ABJURATION, 30);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_EASY);    

    set_ability_stats(STAT_WEIGHTING);

    // Can only cast stoneskin on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "shield_obj");
}

/*
 * Function:    query_stoneskin_ingredients
 * Description: This function defines what components are required for
 *              this stoneskin spell.
 */
public string *
query_stoneskin_ingredients(object caster)
{
    return ({ "chokecherry" });
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
        caster->catch_tell("You can only cast magic shield on yourself!\n");
        return 0;
    }

    if(query_maintained_defensive_caid_spells(caster, "minor") > 2)
    {
        // Allow spell to be renewed
        if("/d/Krynn/guilds/sohm/spells/magic_shield"->has_spell_object(caster))
            return 1;

	caster->catch_tell("You can only maintain three minor spells " +
           "that provide combat utility at any time.\n");
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
    
    if (player->query_npc() || player->query_wiz_level())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"arcanfethos_memorised");
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

        caster_message = "You swifty trace a large circular ward in the air while chanting " +
            "'Arcanfethos!'\n";
        watcher_message = QCTNAME(caster) + " swiftly traces a large circular ward in the air " +
           "while chanting mystical words of magic.\n";
        
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
    write("Your are already protected by a shield of magical force!\n");
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
    write("You need a chokecherry herb to create a shield of magical force.\n");
}

