/*
 * Schirmo Spell for the Elementalists of Calia
 * 
 * This is the elemental shield spell for the elementalists guild of Calia.
 * It allows different types of shields based on different elemental
 * elements, selected by the caster at the time of casting.
 *
 * Fire - grants a damage reflective shield
 * Water - grants regenerative healing shield
 * Air - grants an evasive shield
 * Earth - grants a damage absorbing shield
 *
 * Created by Petros, January 2013
 *
 * Combat aid changed from 25 to 15 following global layman guild review
 * - Arman August 2019.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Defines
#define SCHIRMO_ELEMENT          "_schirmo_element"

// Prototypes
public void resolve_schirmo_spell(object caster, 
	mixed * targets, int * resist, int result);


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
 * Function:    config_schirmo_spell
 * Description: Config function for schirmo spells. Redefine this in your
 *              own schirmo spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_schirmo_spell()
{
    set_ability_group(GUILD_EW_NAME);
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_combat_aid(15.0);
    set_spell_can_be_renewed(1);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
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

    // Spell's element is determined during concentrate_msg and stored.
    int element_skill = player->query_prop(SCHIRMO_ELEMENT);
        
    return element_skill;
}

/*
 * Function name: query_spell_object
 * Description:   Query the spell effect object setting
 */
public mixed
query_spell_object()
{
    // The spell object is different depending on the element
    // This should end up returning whatever specialization the player
    // has for the skill.
    int element_skill = query_spell_element_skill();
    string shield_spell_object = 0;
    
    switch (element_skill)
    {
    case SS_ELEMENT_FIRE:
//        shield_spell_object = "/d/Genesis/specials/std/spells/obj/shadow_obj";
        shield_spell_object = ELEMENTALIST_SPELL_OBJS + "fire_shield_obj";
        break;
    
    case SS_ELEMENT_EARTH:
        shield_spell_object = ELEMENTALIST_SPELL_OBJS + "earth_shield_obj";
        break;
        
    case SS_ELEMENT_WATER:
        shield_spell_object = ELEMENTALIST_SPELL_OBJS + "water_shield_obj";
        break;
        
    case SS_ELEMENT_AIR:
        shield_spell_object = ELEMENTALIST_SPELL_OBJS + "air_shield_obj";
        break;
    
    default:
        // should never happen
        send_debug_message("schirmo", "Unknown element skill for schirmo.\n");
    }
    
    return shield_spell_object;
}

/*
 * Function:    query_schirmo_ingredients
 * Description: This function defines what components are required for
 *              this schirmo spell.
 */
public string *
query_schirmo_ingredients(object caster)
{
    return ({ "_schirmo_component_" });
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
}

/*
 * Function:    spell_target_caster_schirmo
 * Description: A targeting function specific for schirmo. It needs to
 *              parse out the string and set the correct element for
 *              the shield
 */
public object *
spell_target_caster_schirmo(object caster, string str)
{
    string element_string, target_string;
    int element_skill = 0;   
    parse_command((strlen(str) ? str : ""), environment(caster), 
    	"[to] %w [on] %w", element_string, target_string);
    if (strlen(element_string))
    {
        switch (lower_case(element_string))
        {
        case "pyros":
            element_skill = SS_ELEMENT_FIRE;
            break;
        case "aeria":
            element_skill = SS_ELEMENT_AIR;
            break;
        case "gu":
            element_skill = SS_ELEMENT_EARTH;
            break;
        case "diabrecho":
            element_skill = SS_ELEMENT_WATER;
            break;
        }
    }
    if (!element_skill)
    {
        caster->catch_tell("To which Elemental do you wish to pray? "+
        	"Pyros, Aeria, Gu, or Diabrecho?\n");
        return 0;
    }
    caster->add_prop(SCHIRMO_ELEMENT, element_skill);
    
    return spell_target_caster(caster, target_string);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("schirmo");
    set_spell_desc("Encase with an elemental shield");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_caster_schirmo);
    set_spell_ingredients(query_schirmo_ingredients);

    set_spell_fail("You sense your prayers are not heard.\n");
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_ABJURATION, 25);
        
    // Call the specific configuration that is to be masked.
    config_schirmo_spell();
    
    // Call this after the config_schirmo_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_schirmo_spell(caster, targets, resist, result);

    mixed arguments;
    // The spell object is created and moved to the target. It will
    // do all the descriptions in the spell object.
    float aid = query_spell_combat_aid(); // effect uses combat aid
    int element = query_spell_element_skill();
    switch (element)
    {
    case SS_ELEMENT_FIRE:
        arguments = ([ ]);
        arguments["combat_aid"] = ftoi(aid);
        arguments["allow_specials"] = 1;
        arguments["allow_magic_attacks"] = 1;
        arguments["allow_white_attacks"] = 1;
        arguments["exclude_hit_locations"] = ({ });
        arguments["damage_type"] = MAGIC_DT;
        arguments["likelihood"] = 75;
        break;
    
    case SS_ELEMENT_WATER:
    case SS_ELEMENT_AIR:
    case SS_ELEMENT_EARTH:
    default:
        arguments = aid;
    }

    if (query_spell_can_be_renewed())
    {
        mixed * renewed_targets = ({ });
        mixed * remaining_targets = ({ });
        int * remaining_resists = ({ });
        for (int index = 0; index < sizeof(targets); ++index)
        {
            object * existing_objs = 
            	GUILD_MANAGER->get_existing_schirmo_objects(targets[index]);
            if (sizeof(existing_objs))
            {
                existing_objs->renew_spell_duration();
                renewed_targets += ({ targets[index] });
            }
            else
            {
                remaining_targets += ({ targets[index] });
                remaining_resists += ({ resist[index] });
            }
        }
        if (sizeof(renewed_targets))
        {
            hook_renew_spell_object(caster, renewed_targets);
        }
        if (sizeof(remaining_targets))
        {
            make_spell_object(query_spell_object(), caster, 
            	remaining_targets, remaining_resists, result, arguments);    
        }
    }
    else
    {    
        make_spell_object(query_spell_object(), caster, targets, 
        	resist, result, arguments);
    }
}

/*
 * Function name: has_schirmo_object
 * Description:   Checks to see if the target already has one of the schirmo
 *                shields.
 */
public int 
has_schirmo_object(object target)
{
    setuid(); seteuid(getuid());
    object * effects = GUILD_MANAGER->get_existing_schirmo_objects(target);
    if (sizeof(effects))    
    {   
        return 1;
    }
    
    return 0;
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    if (!can_cast_elementalist_spell(caster))
    {
        return 0;
    }

    int element_skill = caster->query_prop(SCHIRMO_ELEMENT);
    if (!GUILD_MANAGER->is_element_carved(caster, element_skill))
    {
        caster->catch_tell("Without having carved the appropriate "+
        	"Word of Power, you cannot hope to invoke the gift of schirmo.\n");
        return 0;
    }

    foreach (object target : targets)
    {
        if ((!query_spell_can_be_renewed() 
             || GUILD_MANAGER->query_active_schirmo_element(target) != 
             query_spell_element_skill())
            && has_schirmo_object(target))
        {
            hook_already_has_spell_object(caster, target);
            return 0;
        }
    }
        
    if (sizeof(GUILD_MANAGER->get_existing_unteristi_objects(caster))
        && GUILD_MANAGER->query_power_spells_combat_aid(caster) > 30)
    {
        caster->catch_tell("You are mentally unable to invoke the power of "
            + "schirmo while maintaining both your Elemental Power spell "
            + "and unteristi.\n");
        return 0;
    }
    
    return result;    
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
    
    // We don't allow the "cast" or "spells" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }
    

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_SCHIRMO)
    {
        return 0;
    }
    return 1;
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_schirmo_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_schirmo_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already shielded by the power of schirmo!\n");
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
    write("You renew the duration of the effect!\n");
}

public string
query_spell_patron()
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
        return "Lord Pyros";
    
    case SS_ELEMENT_EARTH:
        return "Lady Gu";
    
    case SS_ELEMENT_WATER:
        return "Lord Diabrecho";
    
    case SS_ELEMENT_AIR:
        return "Lady Aeria";
    }
    
    return "the Elementals";
}

public string
query_spell_element_description()
{
    switch (query_spell_element_skill())
    {
    case SS_ELEMENT_FIRE:
        return "fire";
    
    case SS_ELEMENT_EARTH:
        return "earth";
    
    case SS_ELEMENT_WATER:
        return "water";
    
    case SS_ELEMENT_AIR:
        return "air";
    }
    
    return "all elements";
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
    switch (random(2))
    {
    case 0:
        caster_message = "You chant the ancient prayer of schirmo unto "
            + query_spell_patron() + ".\n";
        watcher_message = QCTNAME(caster) + " concentrates as " 
            + caster->query_pronoun() + " begins an ancient chant.\n";
        break;
    
    case 1:
    default:
        caster_message = "You draw upon the the power of " + 
        	query_spell_element_description()
            + " as you lift up a prayer to " + query_spell_patron() + ".\n";
        watcher_message = QCTNAME(caster) + " looks deep in concentration "
            + "as " + caster->query_pronoun() + " lifts up " + 
            caster->query_possessive()
            + " arms to the sky in prayer.\n";
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
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "blade, shining bloodstone";
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
