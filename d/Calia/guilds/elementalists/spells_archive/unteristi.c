/*
 * Resistance Spell for the Elemental Worshippers of Calia
 *
 * Created by Petros, December 2010
 *
 * Combat aid changed from 25 to 15 following global layman guild review.
 * MAGIC_I_RES_MAGIC also removed.
 * - Arman August 2019.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/resistance";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes
public object * spell_target_unteristi(object actor, string str);

/*
 * Function:    is_worshipper_defensive_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_worshipper_defensive_spell()
{
    return 1;
}

/*
 * Function:    config_resistance_spell
 * Description: Config function for resistance spells. Redefine this in your
 *              own resistance spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_resistance_spell()
{
    set_ability_group(GUILD_EW_NAME);
    set_spell_name("unteristi");
    set_spell_desc("Enshroud with elemental resistance");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_element(SS_ELEMENT_LIFE, 20); // see query_spell_element_skill
    set_spell_form(SS_FORM_ABJURATION, 20);

    set_spell_object(ELEMENTALIST_SPELL_OBJS + "unteristi_obj");    
    
    set_spell_target(spell_target_unteristi);

    // based on the combat aid benefits outlined in 'man resistance'
    // unteristi provides resistance to six magic types meaning it
    // has a combat aid modifier of x1.3.
    // So for a benefit of 15 caid provides 12 resistance across 
    // the six magic types.

    add_resistance(MAGIC_I_RES_FIRE, 12);  // fire
    add_resistance(MAGIC_I_RES_WATER, 12); // water
    add_resistance(MAGIC_I_RES_AIR, 12);   // air
    add_resistance(MAGIC_I_RES_EARTH, 12); // earth
    add_resistance(MAGIC_I_RES_DEATH, 12); // spirit - evil
    add_resistance(MAGIC_I_RES_LIFE, 12); // spirit - good
}

/*
 * Function:    query_spell_element_skill
 * Description: Returns the actual element skill number that is required
 *              for the spell.
 */
public int
query_spell_element_skill()
{
    // This should end up returning whatever specialization the player
    // has for the skill.
    object player = this_player();

    string primary_element = GUILD_MANAGER->query_primary_element(player);
    int element_skill = SS_ELEMENT_FIRE + random(4); // randomize by default
    switch (primary_element)
    {
    case "fire":
        element_skill = SS_ELEMENT_FIRE;
        break;
    
    case "earth":
        element_skill = SS_ELEMENT_EARTH;
        break;
    
    case "water":
        element_skill = SS_ELEMENT_WATER;
        break;
    
    case "air":
        element_skill = SS_ELEMENT_AIR;
        break;
    }
        
    return element_skill;
}

public object *
spell_target_unteristi(object caster, string str)
{
    if (IS_CLERIC(caster))
    {
        return spell_target_one_present_living(caster, str);
    }
    else
    {
        // Worshippers can only cast on themselves.
        return spell_target_caster(caster, str);
    }
}

/*
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ "_unteristi_component_" });
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
        caster->catch_tell("You can only cast " + query_spell_name() 
            + " on yourself!\n");
        return 0;
    }

    if (sizeof(GUILD_MANAGER->get_existing_schirmo_objects(caster))
        && GUILD_MANAGER->query_power_spells_combat_aid(caster) > 30)
    {
        caster->catch_tell("You are mentally unable to invoke the power of "
            + query_spell_name() + " while maintaining both your Elemental "
            + "Power spell and schirmo.\n");
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
    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_UNTERISTI)
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
        caster_message = "You hold out your palms and lift up a prayer "
            + "to all the Elementals.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palms and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You clasp your hands and fervently pray to all "
            + "the elementals to grant you the protective gifts of "
            + query_spell_name() + ".\n";
        watcher_message = QCTNAME(caster) + " clasps " + 
        	caster->query_possessive()
            + " hands together and concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 5);
    GUILD_MANAGER->add_guild_conduit(5);    
}

/*
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, 
	int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already invoked the gift of " + query_spell_name() + "!\n");
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
    write("You renew the effects of the gift of " + query_spell_name() + "!\n");
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
    write("You need the proper ritual component to summon "
        + "the power of " + query_spell_name() + ".\n");
}

/*
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    // We don't display anything here. All messages are in the spell
    // object
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
    return "athly, purple amethyst";
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
