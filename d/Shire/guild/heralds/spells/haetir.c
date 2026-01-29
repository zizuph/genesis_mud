/*
 * haetir - Prayer to Manwe to give farsight (scry)
 *          Is effective when the target is outdoors.
 *
 * Arman Kharas, May 2018
 */
 
#pragma strict_types

#include <macros.h>
#include <files.h>
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "../herald.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "scry";

public string spell_failure_corruption_check();

/*
 * Function:    query_scry_ingredients
 * Description: This function defines what components are required for
 *              this fartell spell.
 */
public string *
query_scry_ingredients(object caster)
{
    return ({ "parsley" });
}

/*
 * Function:    config_scry_spell
 * Description: Config function for scry spells. Redefine this in your
 *              own scry spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_scry_spell()
{
    set_spell_name("haetir");
    set_spell_desc("Call upon the farsight of Manwe");

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
    set_spell_task(TASK_ROUTINE);    
    set_spell_element(SS_ELEMENT_AIR, 15);
    set_spell_form(SS_FORM_DIVINATION, 25);

    set_spell_fail(spell_failure_corruption_check);
    set_spell_ingredients(query_scry_ingredients);   
}

/*
 * Function:    query_ability_cooldown_time
 * Description: Returns the cooldown time for spells. By default, spells
 *              do not have cooldown times. However, for at will spells,
 *              it has a default of AT_WILL_SPELL_TIME - MINIMUM_SPELL_TIME
 */
public int
query_ability_cooldown_time()
{
    // Layman guild scries require limitations.
    // Recommended minimum limitations include:
    //   * extended cooldown of at least 30 seconds
    //   * limited scry locations (indoors or outdoors only)
    //   * random scry detail (i.e. from room description to domain location)

    int cooldown_time = max(30, (100 - this_player()->query_skill(SS_FORM_DIVINATION)));
    
    return cooldown_time;
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You are still gathering yourself from your last "
        + "casting of " + short() + ".\n");
}

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their spell again.
 */
public void 
hook_special_complete()
{
    write("You feel able to cast " + short() + " again.\n");
}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Scry fail message activated");
    this_player()->spell_failure_corruption_check(query_spell_time());

    return "You fail in your attempt to channel the powers of the Valar.\n";
}

/* 
 * Function:    query_spell_guild_strength
 * Description: This should be overridden by each implementation of
 *              the spell to use elements like guild stat as part of
 *              the guild strength calculation.
 * Returns:     0-100 - scale of the person's strength in the guild.
 *                      Should not exceed 100.
 */
public int
query_spell_guild_strength()
{
    int corruption, level, base_str, str;

    base_str = 40;
    level = 3 * (this_player()->query_herald_level() + 1);
    corruption = min(100, HERALD_CORRUPTION(this_player()));

    str = max(0, min(100, (base_str + level - corruption)));

    // HERALD_DEBUG("Scry guild strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ".");

    return str;
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
    return "parsley";
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
    
    if (IS_MEMBER(player))
    {
        return 1;
    }

    return 0;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    // We want to check corruption level here to see if we can channel

    if (HERALD_CORRUPTION(caster) > 75)
    {
        caster->catch_tell("As a fallen Herald, you can no longer " +
            "channel the powers of the Valar.\n");
        return 0;
    }

    //  If set for singular spell focus and already have an active
    //  maintained spell, spell can't be cast. 
    if(QUERY_HERALD_MAINTAINING(TP) && 
        (QUERY_HERALD_FOCUS(TP) == "singular"))
    {
        caster->catch_tell("You are currently channelling the " +
            "blessings of another greater power, and cannot " +
            "concentrate on another while singularly focused!\n");
        return 0;
    }

    //  If set for dual spell focus and already have two active
    //  maintained spells, spell can't be cast. 
    if((QUERY_HERALD_MAINTAINING(TP) > 1) &&
        (QUERY_HERALD_FOCUS(TP) == "dual"))
    {
        caster->catch_tell("You are currently channelling two " +
            "blessings, and cannot concentrate on another while you " +
            "are dual focused!\n");
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

    caster_message = "You raise your hands and call upon Manwe, Lord " +
        "of the Sky, and channel his farsight in search of " +
        capitalize(arg)+ ".\n";
    watcher_message = QCTNAME(caster)+" raises "+caster->query_possessive()+ 
           " hands in the air and calls upon the aid of Manwe, Lord of " +
           "the Sky.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid()); 
}

/*
 * Function:    resolve_scry_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public status
resolve_scry_spell(object caster, object *targets, int *resist, int result)
{
    object target = targets[0];
    object target_room = environment(target);

    if (objectp(target_room) && target_room->query_prop(ROOM_I_INSIDE))
        return 1;

    return 0;
}

/*
 * Function:    hook_no_scry_message
 * Description: When it is not possible to scry, for whatever reason,
 *              this message is given. This applies to no-scry properties
 *              as well as trying to scry a wizard or someone linkdead.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_no_scry_message(object caster, object target)
{
    caster->catch_tell("Your attempt to divine the location of " +
         "your target is obscured by a mysterious veil.\n");    
}

/*
 * Function:    hook_scry_success
 * Description: When there is a successful scry, a message is prepended
 *              before the room descriptions. This is where you
 *              customize that message.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 *              brief  - whether the description will be brief or not
 */
public void
hook_scry_success(object caster, object target, int brief)
{
    if (brief)
    {
        caster->catch_tell("You channel the farsight of Manwe, seeing " +
            "your target's surroundings from above at a great " +
            "distance.\n");
    }
    else
    {
        caster->catch_tell("You channel the farsight of Manwe, seeing "
            + "them clearly from a birds-eye view above them.\n");
    }

    tell_room(environment(caster), QCTNAME(caster) + " lowers " + 
      caster->query_possessive()+ " hands, looking more " +
      "knowledgeable than before.\n", ({ caster }), caster);
}

/*
 * Function:    hook_scry_failure
 * Description: When the scry fails because of resistance failure, this
 *              message is given. Also given when the target room doesn't
 *              exist.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_scry_failure(object caster, object target)
{
    caster->catch_tell("You attempt to divine the location of your "
        + "target, but something prevents you from doing so.\n");    
}

/*
 * Function:    hook_notify_been_scried_success
 * Description: A person being scried is notified whenever they are scried.
 *              This message is the one that indicates to them that
 *              the scry was successful.
 * Arguments:   caster - person casting the spell
 *              target - the person being scried
 */
public void
hook_notify_been_scried_success(object caster, object target)
{
    target->catch_tell("You sense you are being observed from the skies "
        + "above you.\n");
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */

public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You are missing the herb parsley to channel haetir.\n");
}

/*
 * Function name:   hook_notify_been_scried_failure
 * Description:     A hook added in case of forced failure of the spell. The
 *                  forced failure was added to further be able to customize
 *                  the spell.
 * Arguments:       (object)   caster  - the caster
 *                  (object *) targets - an array of targets
 *                  (int *)    resist  - resistance percentages corresponding to
 *                                       each target
 *                  (int)      result  - how well the spell was cast
 * Returns:         Nothing
 */
public void
hook_scry_force_fail(object caster, object *targets, int *resist, int result)
{
    object target = targets[0];
    
    caster->catch_tell("You channel the farsight of Manwe, but cannot " +
    "find your target from your view from the skies. You " +
    "believe they must be underground or indoors somewhere in " +
    "the domain of " +environment(target)->query_domain()+ ".\n");  
} /* hook_scry_force_fail*/
