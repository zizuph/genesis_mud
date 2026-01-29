/*
 * Stat Boost Spell for the Elemental Worshippers of Calia
 *
 * Created by Petros, August 2011
 *
 * Combat aid modified following global review of layman guilds
 * Arman (AoB) August 2019
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <composite.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/statboost";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

// Prototypes
public object * spell_target_statboost(object actor, string str);

/*
 * Function:    is_worshipper_power_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_worshipper_power_spell()
{
    return 1;
}

/*
 * Function:    config_statboost_spell
 * Description: Config function for stat boost spells. Redefine this in your
 *              own stat boost spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_statboost_spell()
{
    set_ability_group(GUILD_EW_NAME);
    set_spell_name("dynami");
    set_spell_desc("Improve physicals and mentals");
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_HARD);    
    set_spell_can_be_renewed(1);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    // Total maximum boost of 30%
    add_stat_boost(SS_STR, 13);
    add_stat_boost(SS_CON, 13);
    add_stat_boost(SS_DIS, 4);
    
    set_spell_target(spell_target_statboost);

    set_spell_element(SS_ELEMENT_EARTH, 20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);

    // Set the effect object filename
    set_spell_object(ELEMENTALIST_SPELL_OBJS + "dynami_obj");        
}

/*
 * Function:    query_added_stat_boosts
 * Description: Used when making the spell object. This returns the
 *              list of stat boosts that this spell will provide.
 * Returns:     Mapping of the format: SS_* => combat aid
 */
public mapping
query_added_stat_boosts()
{
    mapping max_boosts = ::query_added_stat_boosts() + ([ ]); // make a copy
    if (sizeof(GUILD_MANAGER->query_defensive_spells_active(this_player())) > 1)
    {
        max_boosts[SS_STR] = 7;
        max_boosts[SS_CON] = 7;
        max_boosts[SS_DIS] = 1;
    }
    return max_boosts;
}

public object *
spell_target_statboost(object caster, string str)
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
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this statboost spell.
 */
public string *
query_statboost_ingredients(object caster)
{
    return ({ "_dynami_component_" });
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

    if (!GUILD_MANAGER->is_earth_carved(caster))
    {
        caster->catch_tell("Without having carved the Word of Power into the "
            + "Earth Pentacle, you cannot hope to invoke the gift of "
            + "dynami.\n");
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only invoke the gift of " 
            + query_spell_name() + " upon yourself!\n");
        return 0;
    }

    // If evimero is active, we are not allowed to cast this spell
    if (sizeof(GUILD_MANAGER->get_existing_evimero_objects(caster)))
    {
        caster->catch_tell("You cannot invoke dynami while the Elemental "
            + "Power of evimero is active.\n");
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_DYNAMI)
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
        caster_message = "You press the palms of your hands together and pray "
            + "fervently to Lady Gu for the gift of dynami.\n";
        watcher_message = QCTNAME(caster) + " presses the palms of "
            + caster->query_possessive() + " hands together and prays "
            + "fervently.\n";
        break;
    
    case 1:
    default:
        caster_message = "Clasping your hands together, you concentrate on "
            + "the ancient prayer of Dynami, calling upon Lady Gu to "
            + "provide you with renewed strength.\n";
        watcher_message = QCTNAME(caster) + " clasps " 
            + caster->query_possessive()
            + " hands together as " + caster->query_pronoun() + " mutters "
            + "a prayer.\n";
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
 * Function:    resolve_resistance_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_resistance_spell(object caster, mixed * targets, int * resist, int result)
{
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already received the gift of " + query_spell_name() 
        + "!\n");
}

/*
 * Function:    hook_describe_cast_statboost
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_statboost(object caster, object * targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
//            caster->catch_tell("You cast dynami upon yourself "
//                + "and " + COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("With the realisation that Lady Gu has "
                + "granted your prayer, you feel tranquility penetrate your "
                + "being. A ghostly, more sturdy image of yourself appears "
                + "next to you and moves into you.\n");
        }
    }
    else
    {
//        caster->catch_tell("You cast dynami upon "
//            + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher("A ghostly image of " + QTNAME(caster) + " appears "
        + "next to " + caster->query_objective() + " before moving into "
        + caster->query_objective() + " and disappearing from sight.\n",
        ({ }) );
}

/*
 * Function:    hook_renew_spell_object
 * Description: Message to give when the spell is recast onto an already 
 *              existing effect. Usually just extends the duration of 
 *              the spell
 */
public void
hook_renew_spell_object(object caster, object target)
{
    write("You feel the power of Lady Gu flow into you and renew the effects "
        + "of dynami.\n");
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
    write("You need a proper ritual component as port af "
        + "the gift of " + query_spell_name() + ".\n");
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
    return "cladina, oval turquoise";
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
