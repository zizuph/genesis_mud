/*
 * Featherweight Spell for the Elemental Worshippers of Calia
 *
 * Created by Petros, December 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/featherweight";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

/*
 * Function:    config_featherweight_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_featherweight_spell()
{
    set_ability_group(GUILD_EW_NAME);
    set_spell_name("elefrinisi");
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_ROUTINE);
    // Instead of air, we use earth instead.
    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);
    set_spell_can_be_renewed(1);

    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // Spell effect object
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "elefrinisi_obj");
    
    // Set the weight factor - defaults to 140
    set_weight_factor(140);
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!can_cast_elementalist_spell(caster))
    {
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only request the gift of " + 
        	query_spell_name() 
            + " for yourself!\n");
        return 0;
    }
    
    return 1;
}

/*
 * Function:    query_spell_can_be_learned
 * Description: Determines whether the caster can actually have this spell
 *              in their arsenal.
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
    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_ELEFRINISI)
    {
        return 0;
    }
    return 1;
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
    switch (random(2))
    {
    case 0:
        caster_message = "With a lifting motion of your arms, you call out "
            + "to Lady Gu to grant you relief from your burdens.\n";
        watcher_message = QCTNAME(caster) + " lifts " + 
        	caster->query_possessive()
            + " arms up as " + caster->query_pronoun() + " concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You pray through the ancient chant of elefrinisi "
            + "to Lady Gu.\n";
        watcher_message = QCTNAME(caster) + " looks deep in "
            + "concentration.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 2);
    GUILD_MANAGER->add_guild_conduit(2);    
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
    write("You need a proper ritual component to summon "
        + "the power of elefrinisi.\n");
}

/*
 * Function:    resolve_featherweight_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_featherweight_spell(object caster, mixed * targets, 
	int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    if (caster == target)
    {
        write("Your load is already light as a feather!\n");
    }
    else
    {
        caster->catch_msg("You are already maintaining the ability to lighten " 
            + QTNAME(target) + "'s burdens.\n");
    }
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already 
 *              existing
 *              effect. Usually just extends the duration of the spell
 */
public void
hook_renew_spell_object(object caster, mixed * target)
{
    write("You renew your efforts to be light as a feather!\n");
}

/*
 * Function:    query_featherweight_ingredients
 * Description: This function defines what components are required for
 *              this featherweight spell.
 */
public string *
query_featherweight_ingredients(object caster)
{
    return ({ "_elefrinisi_component_" });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "wildfeather, striped chalcedony";
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "prayers" is used.
 */
public void
list_spells()
{
    string ingredients_description = query_spell_ingredients_description();
    if (!strlen(ingredients_description))
    {
        ingredients_description = "none";
    }
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        ingredients_description));
}
