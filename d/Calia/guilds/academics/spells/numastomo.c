/*
 * Tell Spell for Academy of Elemental Arts
 * 
 * Created by Petros, September 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/fartell";

/*
 * Function:    config_fartell_spell
 * Description: Config function for fartell spells. Redefine this in your
 *              own fartell spells to override the defaults.
 */
public void
config_fartell_spell()
{
    set_spell_name("numastomo");
    set_spell_desc("Communicate with fellow Academics");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_task(TASK_SIMPLE);    
    // Setting lower skill requirements since it's the most basic spell for Academics
    set_spell_element(SS_ELEMENT_AIR, 5);
    set_spell_form(SS_FORM_DIVINATION, 5);
    
    set_can_fartell_unmet(1);
}

/*
 * Function:    query_fartell_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_fartell_ingredients(object caster)
{
    return ({ "silver coin" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    if (!IS_MEMBER(caster))
    {
        caster->catch_tell("You are not a member of the Academy!\n");
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
        caster_message = "You hold your hands up and summon the power "
            + "of the air around you.\n";
        watcher_message = QCTNAME(caster) + " holds up "
            + caster->query_possessive() + " hands and concentrates.\n";
        break;
    
    case 1:
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
    
    setuid();
    seteuid(getuid());
    // Guild masters, Calian wizards, and all members are valid targets
    if (IS_MEMBER(target)
        || IS_GUILDMASTER(target)
        || IS_CALIA_WIZ(target))
    {
        return 1;
    }
    
    // Otherwise, not a valid target.
    return 0;
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
    if (objectp(target_obj) && !IS_MEMBER(target_obj))
    {
        caster->catch_tell("You only know how to manipulate the air to send a "
            + "message to a fellow Academic.\n");
    }
    else
    {
        caster->catch_tell("You do not sense " + capitalize(LANG_POSS(target)) 
            + " presence in the realms.\n");    
    }
}

/*
 * Function:    hook_do_fartell_spell
 * Description: Override this to customize the tell spell descriptions.
 */
public void
hook_do_fartell_spell(object caster, object target, string message_text)
{
    target->catch_msg("The air surrounding you pulses, and you hear a message "
        + "from " + capitalize(caster->query_real_name()) + ":\n\t" 
        + message_text + "\n");
    caster->catch_msg("You create pulses through the air and send a message to " 
        + capitalize(target->query_real_name()) + ":\n\t" 
        + message_text + "\n");
    
    // We add it to the target's tell history
    ACADEMIC_MANAGER->add_tell_message(target, caster->query_real_name(), message_text);
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
    write("You cannot complete your spell without a silver coin.\n");
}

/*
 * Function:    hook_fartell_no_message
 * Description: Override to customize the message for when the caster doesn't
 *              specify a text to send.
 */
public void
hook_fartell_no_message(object caster)
{
    caster->catch_tell("What message do you want to send? (" + query_verb() + " <recipient> <message>)\n");
}

/*
 * Function:    hook_fartell_no_target
 * Description: Override to customize the message for when the caster doesn't
 *              specify a target.
 */
public void
hook_fartell_no_target(object caster)
{
    caster->catch_tell("Who do you want to send a message to? (" + query_verb() + " <recipient> <message>)\n");
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    write(sprintf("%-15s %s (%s)\n", query_spell_name(), ::query_spell_desc(),
        "silver coin"));
}
