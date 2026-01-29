/*
 * Namotir - Protection from death magic spell for Heralds
 *
 * Coded by Arman 2018.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <composite.h>
#include <files.h>
#include "/d/Shire/common/defs.h"
#include "../herald.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "resistance";

public string spell_failure_corruption_check();
public void namotir_resistance_value();

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_resistance_spell()
{
    set_spell_name("namotir");
    set_spell_desc("Protection from Shadow magic");

    set_spell_element(SS_ELEMENT_EARTH,  40);
    set_spell_form(SS_FORM_ABJURATION, 40);
    set_spell_task(TASK_HARD);

    set_spell_fail(spell_failure_corruption_check);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_3);

    // Can only cast namotir on themself
    set_spell_target(spell_target_caster);
  
    set_spell_object(HERALD_SPELLS_OBJ + "namotir_obj");


}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Resist death magic fail message activated");
    this_player()->spell_failure_corruption_check(query_spell_time());

    return "You fail in your attempt to channel the powers of the Valar.\n";
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public void
namotir_resistance_value()
{
    // Combat aid is calculated at 0.8 per 1 point of resistance
    // (see 'man resistance'). With a maximum combat aid of 35, this
    // spell provides a maximum add_resistance of 44 when focused on

    int corruption, level, base_str, str, combat_aid, resist;

    // modifier based on level and corruption
    base_str = 40;
    level = 3 * (this_player()->query_herald_level() + 1);
    corruption = min(100, HERALD_CORRUPTION(this_player()));
    str = max(0, min(100, (base_str + level - corruption)));

    // maximum resistance based on Herald 'focus'
    if(!QUERY_HERALD_FOCUS(this_player()))
    {
        // standard focus: max 15 caid, or 8 to 19 resistance
        resist = 19;
    }
    else if(QUERY_HERALD_FOCUS(this_player()) == "singular")
    {
        // single focus: max 35 caid, 19 to 44 add_resistance
        resist = 44;
    }
    else    
    {
        // dual focus: max 22 caid, 12 to 28 add_resistance
        resist = 28;
    }

    // HERALD_DEBUG("Base resist: " + resist + ".");

    // modify resistance based on guild level and corruption

    resist = resist * str / 100;

    // HERALD_DEBUG("Modified resist: " + resist + ".");

    add_resistance(MAGIC_I_RES_DEATH, resist);    
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
 * Function:    query_resistance_ingredients
 * Description: This function defines what components are required for
 *              this resistance spell.
 */
public string *
query_resistance_ingredients(object caster)
{
    return ({ "nasturtium", "blackroot"});
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
    return "nasturtium, blackroot";
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
    namotir_resistance_value();
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
    write("You are missing an ingredient to channel namotir!\n");
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

    caster_message = "You call upon Namo, the Keeper of the Dead, and " +
        "channel his mastery of the afterlife to protect you from " +
        "death magics.\n";
    watcher_message = QCTNAME(caster) + " channels Namo, the Keeper of " +
        "the Dead, calling upon his protection.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid());  
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

/*
 * Function:    hook_describe_cast_resistance
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_resistance(object caster, object * targets)
{
    object * message_targets = targets + ({ });
    message_targets -= ({ caster });
    if (IN_ARRAY(caster, targets))
    {
        if (sizeof(message_targets))
        {
            caster->catch_tell("You channel Namo's protection from death " +
                "magics upon yourself and " + 
                COMPOSITE_LIVE(message_targets) + ".\n");
        }
        else
        {
            // No message needed.
        }
    }
    else
    {
        caster->catch_tell("You channel Namo's protection from death " +
            "magics upon " + COMPOSITE_LIVE(message_targets) + ".\n");
    }
    caster->tell_watcher(QCTNAME(caster) + " channels the " +
        "protection of Namo, Keeper of the Dead.\n", ({ }) );
}
