/*
 * Noleme - Wisdom of Ulmo.
 *
 * Arman Kharas, May 2018
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "statboost";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#include "../herald.h"

#include <macros.h>
#include <tasks.h>

public string spell_failure_corruption_check();

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
    set_spell_name("noleme");
    set_spell_desc("Channel the wisdom of Ulmo");

    set_spell_task(TASK_HARD);
    set_spell_element(SS_ELEMENT_WATER,  30);
    set_spell_form(SS_FORM_CONJURATION, 30);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);

    set_spell_fail(spell_failure_corruption_check);

    // Can only cast oheroism on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(HERALD_SPELLS_OBJ + "noleme_obj");

    // stat boosted up to a maximum of 35 caid depending on
    // guild rank and corruption negatives. Modified under
    // query_spell_guild_strength
    add_stat_boost(SS_WIS, 35);
    // added to support sustained mana calculations
    set_spell_combat_aid(35.0);

}


public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Wis boost fail message activated");
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

    // wisdom bonus dependent on guild level and focus
    int base_wis = 60;

    base_str = 40;
    level = 3 * (this_player()->query_herald_level() + 1);
    corruption = min(100, HERALD_CORRUPTION(this_player()));

    str = max(0, min(100, (base_str + level - corruption)));

    base_wis = (base_wis * str) / 100;

    // benefit modified on Herald 'focus'
    if(!QUERY_HERALD_FOCUS(this_player()))
    {
        // standard focus: max 15 caid, float_str divided by 2.4
        base_wis = ftoi(itof(base_wis) / 2.4);
    }
    else if(QUERY_HERALD_FOCUS(this_player()) == "singular")
    {
        // single focus: max 35 caid, no modifier
        base_wis = base_wis;
    }
    else    
    {
        // dual focus: max 22 caid, str divided by 1.6
        base_wis = ftoi(itof(base_wis) / 1.6);
    }

    add_stat_boost(SS_WIS, base_wis);

   // HERALD_DEBUG("Wis boost strength: " +str+ ", lvl: " +level+ 
   //     ", corruption: " +corruption+ ", wis boost: " +base_wis+ ".");

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
 * Function:    query_statboost_ingredients
 * Description: This function defines what components are required for
 *              this stat boost spell.
 */
public string *
query_statboost_ingredients(object caster)
{
    return ({ "adillyp weed", "_shire_lily_" });
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
    return "adillyp weed, water lily";
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

    //  No more than three caid maintained spells can be cast at any
    //  one time. 
    if(QUERY_HERALD_MAINTAINING(TP) > 2)
    {
        caster->catch_tell("You mentally cannot channel any more " +
            "blessings of this nature.\n");
        return 0;
    }

    return 1;
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are already channelling the wisdom of Ulmo!\n");
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
    write("You are missing an ingredient to channel the wisdom of " +
        "Ulmo!\n");
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

    caster_message = "You close your eyes and visualise a tranquil calm " +
        "ocean, before calling upon the wisdom of Ulmo, Master of " +
        "Waters.\n";
    watcher_message = QCTNAME(caster) + " relaxes and closes " +
        HIS_HER(caster)+ " eyes before calling upon Ulmo, Master " +
        "of Waters.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid());  
}

/*
 * Function:    hook_describe_cast_statboost
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_statboost(object caster, object * targets)
{
}

