/*
 * Self Healing Spell for the Elemental Guilds of Calia
 *
 * Created by Petros, December 2010
 *
 * Combat aid modified following global review of layman guilds
 * Arman (AoB) August 2019
 */

#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/heal";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

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
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_heal_spell()
{
    set_ability_group(GUILD_EW_NAME);
    set_spell_name("aleipso");
    set_spell_desc("Heal yourself or other");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_HARD);    
    set_spell_combat_aid(50.0);
    set_spell_time_factor(2.0); // takes double the normal time of spells

    // No longer restricted on who you can cast it on.
    // set_spell_target(spell_target_caster);

    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    
    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_ENCHANTMENT, 25);
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    // If the player has both defensive spells on, we reduce the
    // total combat aid provided by this spell.

    // Whether defensive spells are active has no impact on caid 
    // of this spell anymore.
/*
    if (sizeof(GUILD_MANAGER->query_defensive_spells_active(this_player())) > 1)
    {
        return 100.0 * 30.0 / 55.0;    
    }
*/
    
    return 100.0;
}

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    // One herb, and one leftover. No gem requirements
    return ({ "_aleipso_component_" });
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

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_ALEIPSO)
    {
        return 0;
    }
    return 1;
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

    // If either dynami or evimero are active, we are not allowed to cast this 
    // spell
    if (sizeof(GUILD_MANAGER->query_power_spells_active(caster)))
    {
        caster->catch_tell("You cannot invoke aleipso while another Elemental "+
            "Power prayer is active.\n");
        return 0;
    }

    if (!GUILD_MANAGER->is_water_carved(caster))
    {
        caster->catch_tell("Without having carved the Word of Power into the "+
            "Water Chalice, you cannot hope to invoke the gift of aleipso.\n");
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
        caster_message = "You hold out your palm with the fingers pointed "
            + "away from you and focus on gathering the power of the "
            + "moisture in the air as you seek Lord Diabrecho's succor.\n";
        watcher_message = QCTNAME(caster) + " holds out "
            + caster->query_possessive() + " palm and concentrates.\n";
        break;
    
    case 1:
    default:
        caster_message = "You summon your inner reserves of power and "
            + "focus your mind on utilizing the element of water.\n";
        watcher_message = QCTNAME(caster) + " closes "
            + caster->query_possessive() + " eyes and concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    
    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 2);
    GUILD_MANAGER->add_guild_conduit(2);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_heal_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
    if (IN_ARRAY(caster, targets))
    {
        object * other_targets = targets - ({ caster });
        if (sizeof(other_targets))
        {
            caster->catch_tell("Moisture in the air coalesces into "
                + "thin streams of water that direct themselves to "
                + COMPOSITE_LIVE(other_targets) + " and yourself and "
                + "covers up your injuries.\n");
        }
        else
        {
            caster->catch_tell("Moisture in the air coalesces into "
                + "thin streams of water that direct themselves to your "
                + "injuries.\n");
        }
    }
    else
    {
        caster->catch_tell("Moisture in the air coalesces into thin "
            + "streams of water that direct themselves to "
            + COMPOSITE_LIVE(targets) + " and covers up their "
            + "injuries.\n");
    }
}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        switch (heal_amounts[index])
        {
        case 0:
            tell_room(environment(caster), QCTNAME(target)
                + " doesn't look any healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body, but does not make you "
                + "any healthier.\n");
            break;
        
        case 1..100:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body and closes a few of your "
                + "wounds.\n");
            break;
            
        case 101..250:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body and closes quite a few of your "
                + "wounds.\n");
            break;
        
        case 251..500:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body and closes many of your "
                + "wounds.\n");
            break;

        default:
            tell_room(environment(caster), QCTNAME(target)
                + " looks healthier.\n", targets);
            target->catch_tell("The healing water of Lord Diabrecho "
                + "traverses your body, closes your wounds, and "
                + "makes you a lot healthier.\n");
            break;            
        }
    }
}


/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        switch (harm_amounts[index])
        {
        case 0:
            tell_room(environment(caster), QCTNAME(target)
                + " doesn't look phased by the living energy.\n", targets);
            target->catch_tell("Living energies enter your body, but "
                + "you are unphazed.\n");
            break;
        
        case 1..100:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you slightly.\n");
            break;
            
        case 101..250:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you somewhat.\n");
            break;
        
        case 251..500:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you moderately.\n");
            break;

        default:
            tell_room(environment(caster), QCTNAME(target)
                + " looks hurt by the living energies.\n", targets);
            target->catch_tell("Living energies enter your body, and "
                + "hurt you greatly.\n");
            break;
        }
    }
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
    write("You need a proper ritual component as part of "
        + "the prayer of " + query_spell_name() + " to Lord "
        + "Diabrecho.\n");
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
    return "strim, white pearl";
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
