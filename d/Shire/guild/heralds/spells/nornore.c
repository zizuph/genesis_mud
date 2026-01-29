/*
 * Nornore - Detect other Heralds are in the realms. Cosmetic spell.
 *
 * Arman Kharas, May 2018
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "../herald.h"
#include "/d/Shire/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "shadow";

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{
    set_spell_name("nornore");
    set_spell_desc("Detect other Heralds in the realms");

    set_spell_element(SS_ELEMENT_EARTH,  10);
    set_spell_form(SS_FORM_DIVINATION, 5);
    set_spell_fail("You fail in your attempt to channel the powers " +
        "of the Valar.\n");

    // Reduced mana and difficulty - essentially a cosmetic spell
    set_spell_mana(5);
    set_spell_task(TASK_SIMPLE);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_0);

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast on self
    set_spell_target(spell_target_caster);
   
    set_shadow_filename(HERALD_SPELLS_OBJ + "nornore_sh");
}

/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{
    return ({ });
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

    caster_message = "You begin channelling the bonds of friendship " +
        "and loyalty of Astaldo, divining insights into the other " +
        "Heralds of the Valar who currently walk the realms.\n";
    watcher_message = QCTNAME(caster) + " begins channelling, " +
        "attempting to divine insights from Astaldo.\n";
        
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
