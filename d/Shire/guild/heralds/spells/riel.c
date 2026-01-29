/*
 * riel - Channel Yavannah to create herb gardens (plant)      
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
#include <language.h>
#include "/d/Shire/sys/defs.h"
#include "../herald.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "plant";

public string spell_failure_corruption_check();

#define RIEL_ROOM_OBJ "/d/Shire/guild/heralds/spells/obj/riel_room_obj"

/*
 * Function:    config_plant_spell
 * Description: Config function for plant spells. Redefine this in your
 *              own plant spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_plant_spell()
{
    set_spell_name("riel");
    set_spell_desc("Create a herb garden by channelling the Earth-mother");

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);

    set_spell_task(TASK_ROUTINE);    
    set_spell_element(SS_ELEMENT_EARTH, 45);
    set_spell_form(SS_FORM_CONJURATION, 25);

    set_spell_fail(spell_failure_corruption_check);  
}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Plant fail message activated");
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

    // HERALD_DEBUG("Plant guild strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ".");

    return str;
}

/*
 * Function:    query_plant_ingredients
 * Description: This function defines what components are required for
 *              this plant spell.
 */
public string *
query_plant_ingredients(object caster)
{
    return ({ "opal","water","ashes" });
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
    return "opal, water, ashes";
}

void
hook_use_ingredients(object *ingrs)
{
    int j, k, l; // ashes, water, opal
    string *arr;
     
    if(ingrs[0]->id("water"))
    {
       if(ingrs[2]->id("opal")) 
       {      
           j = 1;
           k = 0;
           l = 2;
       }
       else
       {      
           j = 2;
           k = 0;
           l = 1;
       }
    }
    if(ingrs[0]->id("ashes"))
    {
       if(ingrs[2]->id("opal")) 
       {      
           k = 1;
           j = 0;
           l = 2;
       }
       else
       {      
           k = 2;
           j = 0;
           l = 1;
       }
    }
    else
    {
       if(ingrs[2]->id("water")) 
       {      
           k = 2;
           j = 1;
           l = 0;
       }
       else
       {      
           k = 1;
           j = 2;
           l = 0;
       }
    }

    write("You scatter " + LANG_THESHORT(ingrs[j]) + " before you, " +
        "and then pour " + LANG_THESHORT(ingrs[k]) + " on the ground " +
        "in thanks to Yavanna. " +capitalize(LANG_THESHORT(ingrs[l]))+
        " glows radiantly before crumbling to fine dust and blowing " +
        "away.\n");

    say(QCTNAME(TP)+ " scatters " + LANG_THESHORT(ingrs[j]) + " around " +
        HIM_HER(TP)+ "self, and then pours " + LANG_THESHORT(ingrs[k]) + 
        " on to the ground before giving thanks to Yavanna, the " +
        "Earth-mother.\n");
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

    caster_message = "You lower yourself to the ground and call upon " +
        "Yavanna the Earth-mother, Keeper of Plants, for her " +
        "endowment and the sanctification of the ground before you.\n";
    watcher_message = QCTNAME(caster)+" lowers "+HIM_HER(caster)+ 
        "self to the ground and calls upon Yavanna, the Earth-mother.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid()); 
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
    write("You are missing an opal, water or ashes to channel the blessings " +
        "of Yavanna.\n");
}

/*
 * Function:    hook_describe_plant_success
 * Description: Mask this function to describe the message that occurs when
 *              the spell completes successfully and herbs are planted. It
 *              gives a list of all the herbs prior to planting and all the
 *              shards resulting from the plant.
 */
public void
hook_describe_plant_success(object caster, object herb)
{
    object riel_room_obj;
    int value = herb->query_herb_value();

    tell_room(environment(caster), "The earth before you pulses with " +
        "nurturing warmth, drawing the " + herb->singular_short(herb) + 
        " down into the ground.\n");

    riel_room_obj = clone_object(RIEL_ROOM_OBJ);
    riel_room_obj->set_remove_riel(value, herb);
    riel_room_obj->move(environment(caster), 1);
}

/*
 * Function:    hook_describe_plant_no_valid_herb_precast
 * Description: Mask this function to describe the message that occurs when the
 *              caster doesn't find any herbs. Called from check_valid_action
 */
public void
hook_describe_plant_no_valid_herb_precast(object caster)
{
    caster->catch_tell("You don't find anything on the ground that you "
        + "can plant.\n");
}

/*
 * Function:    hook_describe_plant_no_valid_herb_postcast
 * Description: Mask this function to describe the message that occurs when
 *              the caster completes the spell, but finds no valid herbs
 *              to plant. This can occur if someone picks up the herbs,
 *              for example.
 */
public void
hook_describe_plant_no_valid_herb_postcast(object caster)
{
    caster->catch_tell("You realize much too late that there are no herbs "
        + "on the ground and your prayer has no effect.\n");
}

/*
 * Function:    hook_describe_plant_no_valid_room
 * Description: Mask this function to describe the message that occurs when
 *              the caster tries to plant something in a room that has no
 *              other herbs already defined.
 */
public void
hook_describe_plant_no_valid_room(object caster)
{
    caster->catch_tell("This area doesn't seem to be suitable for "
        + "planting herbs. You may want to try again elsewhere.\n");
}
