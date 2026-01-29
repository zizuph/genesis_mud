/*
 * engwagalad - Pray to Lorien to tend your injuries.
 *
 * May use athelas as an optional herb to double the power of the spell
 *
 * Arman Kharas, May 2018
 */

#pragma strict_types

inherit "/d/Genesis/specials/new/magic/spells/cleanse";

#include "../herald.h"
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <files.h>
#include <composite.h>

#include <macros.h>
#include <tasks.h>

public string spell_failure_corruption_check();

// Global variables
static mapping special_ingredient = ([]);


/*
 * Function:    config_cleanse_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 */
public void
config_cleanse_spell(void)
{
    set_spell_name("engwagalad");
    set_spell_desc("A prayer to Lorien to tend poisons and inflictions");

    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_fail(spell_failure_corruption_check);

    set_spell_task(TASK_ROUTINE);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_optional_ingredients(({ "athelas" }));
}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Cleanse fail message activated");
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

    // HERALD_DEBUG("Cleanse strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ".");

    return str;
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{    
    return 100.0;
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
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_cleanse_ingredients(object caster)
{
    return ({ "pawnrose" });
}

void
hook_use_ingredients(object *ingrs)
{
    string i, j;

    if(sizeof(ingrs) > 1)
    {
        i = ingrs[0]->query_herb_name();
        j = ingrs[1]->query_herb_name();

        // HERALD_DEBUG("Cleanse herbs: " +i+ " " +j+ ".");
        write("As you crush the petals of the green rose together with " +
            "the green leaf known as kingsfoil, a strong " +
            "calming and fragrant scent rises to your nostrils.\n");
    }
    else
    {
        write("As you crush the petals of the green rose in your hand, " +
            "a fragrant scent rises to your nostrils.\n");
    }
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
    return "pawnrose";
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
 * Function:    resolve_cleanse_spell
 * Description: Called at the beginning of resolve_spell in order to perform 
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_cleanse_spell(object caster, mixed * targets, int * resist, int result)
{
    // Modify the result depending on query_spell_guild_strength() seeing
    // it doesn't seem the base cleanse spell picks it up.

    // HERALD_DEBUG("Cleanse base result: " +result+ ".");

    int guild_str = query_spell_guild_strength();   
    result = result * guild_str / 100;

    // HERALD_DEBUG("Cleanse guild stat result: " +result+ ".");

    // If using the optional ingredient athelas, the cleanse is twice as 
    // potent
    if (special_ingredient[caster])
    {
        result = result * 2;
        // HERALD_DEBUG("Cleanse result with athelas: " +result+ ".");
    }
    else
    {
        // HERALD_DEBUG("Cleanse result without athelas: " +result+ ".");
    }
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

    if(target->query_alignment() < -79)
    {
        caster_message = "You supplicate Lorien to cure the afflicted, " +
            "although feel your actions may be in aid of Darkness " +
            "and putting you at risk of corruption by the Shadow of " +
            "Mordor.\n"; 

        ADD_CORRUPTION(caster, 1); 
    }  
    else
        caster_message = "You whisper a prayer, supplicating Lorien " +
            "to cure the afflicted.\n";

    watcher_message = QCTNAME(caster) + " whispers a prayer to Lorien.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid());  
}

public void
hook_describe_cleanse_cast(object caster, object * targets)
{
    object target = targets[0];
    if (caster == target)
    {
	caster->catch_tell("You channel Lorien to purge you of " +
            "poisons and inflictions.\n");
	tell_room(environment(caster), QCTNAME(caster) +
	    " channels Lorien.\n", targets);

    }
    else
    {
        caster->catch_msg("You channel Lorien to cure "+ 
            QTNAME(target) + " of poisons and afflictions.\n");    
        target->catch_msg(QCTNAME(caster) + " channels " +
            "Lorien to cure you of poisons and afflictions.\n");
        tell_room(environment(caster), QCTNAME(caster) + 
            " channels Lorien to cure "+ QTNAME(target) + 
            " of poisons and afflictions.\n", ({ caster, target }) );
    }
    
}

public void
hook_no_cleanseable_poisons(object caster, object target)
{
    caster->catch_tell("You find nothing to cure.\n");    
}

public void
hook_no_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You fail to cure any poisons from your body.\n");
   }
   else
   {
       caster->catch_msg("You fail to cure any poisons from "
        + QTPNAME(target) + " body.\n");
   }
}

public void
hook_all_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You successfully cure all poisons from your body.\n");
   }
   else
   {
       caster->catch_tell("You successfully cure all poisons from " +
                          COMPOSITE_LIVE(target)+ ".\n");
       target->catch_msg(QCTNAME(caster) + " cures all of your poisons.\n");
   }
}

public void
hook_some_poisons_cleansed(object caster, object target)
{
   if (caster == target)
   {
       caster->catch_msg("You manage to cure some of the poisons from " +
                         "your body.\n");
   }
   else
   {
       caster->catch_tell("You manage to cure some poisons from " +
        COMPOSITE_LIVE(target)+  ", but some still remain.\n");
       target->catch_msg(QCTNAME(caster) + " cures some of your poisons, "
        + "but some still remain.\n");
   } 

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
    write("You are missing the herb pawnrose to channel engwagalad.\n");
}

static mixed * 
check_required_items(object actor, mixed * targets, string arg, int pretest)
{
    mixed *items = ::check_required_items(actor, targets, arg, pretest);
    
    if (sizeof(items) > sizeof(query_cleanse_ingredients(actor)))
        special_ingredient[actor] = 1;
    else
        special_ingredient[actor] = 0;
    
    return items;
}
