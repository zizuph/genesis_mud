/*
 * khil - detect alignment
 *
 * Arman Kharas, May 2018
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "alignment";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "../herald.h"
#include "/d/Shire/sys/defs.h"

#include <macros.h>
#include <tasks.h>

public string spell_failure_corruption_check();

/*
 * Function:    config_calm_spell
 * Description: Config function for calm spells. Redefine this in your
 *              own calm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void 
config_alignment_spell()
{
    set_spell_name("khil");
    set_spell_desc("Call Vaire to divine the touch of Shadow");

    set_spell_element(SS_ELEMENT_EARTH, 10);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_fail(spell_failure_corruption_check);

    set_spell_task(TASK_HARD);
    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);
}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Detect evil fail message activated");
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

    // HERALD_DEBUG("Detect evil strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ".");

    return str;
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

    if (IS_MEMBER(player))
    {
        return 1;
    }

    return 0;
}

/*
 * Function:    query_calm_ingredients
 * Description: This function defines what components are required for
 *              this calm spell.
 */
public string *
query_alignment_ingredients(object caster)
{
    return ({  });
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

/*
 * Function:    resolve_refresh_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_alignment_spell(object caster, mixed * targets, int * resist, int result)
{

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
    object target = targets[0];

    caster_message = "You beseech Vaire the Weaver for access to her " +
        "Loom of Time, searching the threads tied to the deeds of " +
        COMPOSITE_LIVE(targets)+ " for signs of darkness.\n";
    watcher_message = QCTNAME(caster) + " beseeches Vaire the Weaver " +
        "for divine insights.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid());  
}

/*
 * Function name : hook_report_alignment
 * Description   : Hook method to be masked to provide your own descriptions
 *                 of the alignment.
 *
 * Arguments  : object caster        - The caster of the spell.
 *            : object target        - The target of the spell, who to check the alignment for.
 *            : int target_alignment - The alignment of the target.
 *            : int result           - Result of the spell cast, how well it was cast.
 */
public void
hook_report_alignment(object caster, object target, int target_alignment, int result)
{

    switch(target_alignment)
    {
        case -1200..-800:
            caster->catch_msg(QCTPNAME(target) + " deeds indicate " +
                HE_SHE(target) + "is lost in the darkness of Melkor.\n");
             break;
        case -799..-300:
            caster->catch_msg(QCTPNAME(target) + " deeds indicate " +
                HE_SHE(target) + " knows darkness well.\n");
             break;
        case -299..-1:
            caster->catch_msg(QCTPNAME(target) + " deeds indicate " +
                HE_SHE(target) + " is beginning to gather darkness.\n");
             break;
        case 0..300:
            caster->catch_msg(QCTPNAME(target) + " deeds indicate " +
                HE_SHE(target) + " is not captured by the darkness.\n");
             break;
        case 301..799:
            caster->catch_msg(QCTPNAME(target) + " deeds indicate " +
                HE_SHE(target) + " seems to know something of the " +
                "Valar.\n");
        case 800..1200:
            caster->catch_msg(QCTPNAME(target) + " deeds indicate " +
                HE_SHE(target) + " is a true enemy of Melkor.\n");
             break;
        default:
             caster->catch_msg(QCTNAME(target) + " baffles you.\n");
             break;
    }  
}
