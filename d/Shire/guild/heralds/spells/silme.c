/*
 * Silme - Light spell.
 *
 * Arman Kharas, May 2018
 */
 
#pragma strict_types

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "light";

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "/d/Shire/sys/defs.h"
#include "../herald.h"

public string spell_failure_corruption_check();

/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_light_spell()
{
    set_spell_name("silme");
    set_spell_desc("Appeal to Elbereth to light your way");

    set_spell_element(SS_ELEMENT_AIR,  10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail(spell_failure_corruption_check);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_1);
   
    set_spell_object(HERALD_SPELLS_OBJ + "silme_obj");
}

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Light fail message activated");
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

    // HERALD_DEBUG("Light guild strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ".");

    return str;
}

/*
 * Function:    query_light_ingredients
 * Description: This function defines what components are required for
 *              this light spell.
 */
public string *
query_light_ingredients(object caster)
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

public object *
spell_target_herald_robe(object caster)
{
    object robe = present("_herald_robe_", caster);

    if (!objectp(robe))
    {
	caster->catch_tell("You are unable to pray for this spell "+
	    "without your robe!\n");
	return ({ });
    }
    if (!robe->query_worn())
    {
	caster->catch_tell("Your "+robe->short()+" must be worn "+
	    "in order to pray for this spell.\n");
	return ({ });
    }
    return ({ robe });
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
    object *robe = spell_target_herald_robe(caster);

    // If in Middle Earth at night outside, unique message

    if(caster->check_herald_location() && 
       environment(caster)->query_prop(ROOM_I_INSIDE) &&
       environment(caster)->query_sunlight() == 0)
    {
        caster_message = "You raise your hands to the night sky and " +
            "call upon Elbereth, channelling the radiant beauty of " +
            "her wondrous creations - the stars.\n";
        watcher_message = QCTNAME(caster) + " raises " +HIS_HER(caster)+ 
            "hands to the night sky and call upon Elbereth, channelling " +
            "the radiance of the stars.\n";
    }
    else
    {
        caster_message = "You chant a prayer to Elbereth, the embodiment "+
            "of light, to guide you with her radiance.\n";
        watcher_message = QCTNAME(caster) + " raises "+ HIS_HER(caster)+  
            " hands in the air, chanting softly to Varda.\n";
    }
        
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

    return 1;
}
