/*
 * Tell Spell for Elemental Clerics of Calia
 * 
 * Created by Jaacar, January 2017
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "fartell";
inherit (ELEMENTALIST_SPELLS + "spell_functions");

/*
 * Function:    is_child_cleric_spell
 * Description: Used for filtering spells into the right categories
 */
public int
is_child_cleric_spell()
{
    return 1;
}

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 */
public void
config_fartell_spell()
{
    set_spell_name("anemos");
    set_spell_desc("Communicate with others far away");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_1);
    set_spell_task(TASK_SIMPLE);    
    
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");
    
    // Setting lower skill requirements since it's the most basic spell
    set_spell_element(SS_ELEMENT_AIR, 5);
    set_spell_form(SS_FORM_CONJURATION, 5);
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_fartell_ingredients(object caster)
{
    return ({  });
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
    switch (random(3))
    {
    case 0:
        caster_message = "You hold your hands up and summon the power "
            + "of the air around you.\n";
        watcher_message = QCTNAME(caster) + " holds up "
            + caster->query_possessive() + " hands and concentrates.\n";
        break;
    
    case 1:
        caster_message = "You concentrate on the winds around you as "
            + "you whisper a message to be carried across the realms.\n";
        watcher_message = QCTNAME(caster) + " has a faraway look in "
            + caster->query_possessive() + " eyes as "
            + caster->query_pronoun() + " concentrates.\n";
        break;
        
    default:
        caster_message = "You draw upon your inner reserves as you "
            + "focus on the air around you.\n";
        watcher_message = QCTNAME(caster) + " has a faraway look in "
            + caster->query_possessive() + " eyes as "
            + caster->query_pronoun() + " concentrates.\n";
        break;
    }
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);
    setuid();
    seteuid(getuid());
    GUILD_MANAGER->add_practice_level(caster, 1);
    
}

/*
 * Function:    resolve_fartell_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_fartell_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    is_valid_fartell_target
 * Description: Called from target_fartell_spell, a customized spell should
 *              mask this and add any restrictions (such as guild members)
 *              on top of the base restrictions in targetting.
 * Returns:     0/1 - not valid/valid target
 */
public int
is_valid_fartell_target(object caster, object target)
{
    if (!objectp(target) || !interactive(target))
    {
        return 0;
    }
    
    if(target->query_wiz_level() && !IS_CALIA_WIZ(target))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function:    hook_fartell_target_unavailable
 * Description: Override to customize the message for when the target cannot
 *              be reached. This includes invis wizards
 */
public void
hook_fartell_target_unavailable(object caster, string target)
{
    caster->catch_tell("You do not sense " + capitalize(LANG_POSS(target)) 
        + " presence in the realms.\n");    
}

/*
 * Function:    hook_fartell_target_not_valid
 * Description: Override to customize the message for when the target cannot
 *              be reached because is_valid_fartell_target returns false
 */
public void
hook_fartell_target_not_valid(object caster, string target)
{
    object target_obj = find_player(target);
    caster->catch_tell("You do not sense " + capitalize(LANG_POSS(target)) 
        + " presence in the realms.\n");    
}

/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    if (environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        target->catch_msg("\nThe water around your ear vibrates, carrying the "
            + "voice of " + capitalize(caster->query_real_name()) +
            " saying:\n\t" + message_text + "\n\n");
    }
    else
    {        
        target->catch_msg("\nA soft wind blows around your ears, carrying the "
            + "voice of " + capitalize(caster->query_real_name()) +
            " whispering:\n\t" + message_text + "\n\n");
    }    
    caster->catch_msg("You use the power of Anemos to speak to " 
        + capitalize(target->query_real_name()) + ":\n\t" 
        + message_text + "\n");
    // We add it to the target's tell history
    GUILD_MANAGER->add_tell_message(target, caster->query_real_name(),
        message_text);
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
    write("You cannot pray to Lady Aeria for the gift of Anemos without a "+
        "silver coin.\n");
}

/*
 * Function:    hook_fartell_no_message
 * Description: Override to customize the message for when the caster doesn't
 *              specify a text to send.
 */
public void
hook_fartell_no_message(object caster)
{
    caster->catch_tell("What message do you want to send? (" + query_verb() +
        " anemos <recipient> <message>)\n");
}

/*
 * Function:    hook_fartell_no_target
 * Description: Override to customize the message for when the caster doesn't
 *              specify a target.
 */
public void
hook_fartell_no_target(object caster)
{
    caster->catch_tell("Who do you want to send a message to? (" +
        query_verb() + " anemos <recipient> <message>)\n");
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
    
    if (player->query_wiz_level())
    {
        // Wizards get all spells
        return 1;
    }
    
    // We don't allow the "cast" verb to be used
    if (calling_function(-1) == "cast" || calling_function(-1) == "spells")
    {
        return 0;
    }

    if (player->query_stat(SS_LAYMAN) < SPELL_MINIMUM_GSTAT_CLERIC_ANEMOS)
    {
        return 0;
    }
    return 1;
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
    return "none";
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
