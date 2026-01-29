/*
 * Rada - find herbs prayer
 *
 * Arman Kharas - May 2018
 */
#pragma strict_types

#include <stdproperties.h>
#include <language.h>
#include <tasks.h>
#include "/d/Shire/common/defs.h"
#include "../herald.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "unfinished/locate";

// Prototypes
public object *spell_locate_target(object actor, string arg);
public string spell_failure_corruption_check();

// Global Variable
static mapping target_locate = ([]);

/*
 * Function name:   config_locate_spell
 * Description:     Config function for locate spells. Redefine this in your own
 *                  locate spells to override the defaults.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
config_locate_spell()
{
    set_spell_name("rada");
    set_spell_desc("Call upon Vana to find nearby herbs");

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_EARTH,  20);
    set_spell_form(SS_FORM_DIVINATION, 20);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_2);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_stationary(1);
    set_spell_can_be_renewed(0);
    
    set_spell_target(spell_locate_target);
    set_spell_fail(spell_failure_corruption_check);
    set_shadow_filename(HERALD_SPELLS_OBJ + "rada_sh");
    
    // The size of the radius in which we expand our concentric locating circle
    // Example: 1 - All the rooms that are adjacent to ours.
    //          2 - All the rooms that are adjacent to the rooms in 1.
    //          3 - All the rooms that are adjacent to the rooms in 2.
    //          ... And so on
    set_locate_limit(4);

    // Results in multiple paths
    set_multiple_checks(1);
} /* config_locate_spell */

public string 
spell_failure_corruption_check()
{
    // HERALD_DEBUG("Locate fail message activated");
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
    int locate = 4 + ((this_player()->query_herald_level() + 1) / 2);

    base_str = 40;
    level = 3 * (this_player()->query_herald_level() + 1);
    corruption = min(100, HERALD_CORRUPTION(this_player()));

    str = max(0, min(100, (base_str + level - corruption)));
    locate = (locate * str) / 100;

    // HERALD_DEBUG("Locate strength: " +str+ ", lvl: " +level+ 
    //    ", corruption: " +corruption+ ", locate range: " +locate+ ".");

    set_locate_limit(locate);

    return str;
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
 * Function name:   query_locate_ingredients
 * Description:     This function defines what components are required for this
 *                  locate spell.
 * Arguments:       (object) caster - The caster in whom we look for ingredients
 * Returns:         (string *) - Array of ingredient strings
 */
public string *
query_locate_ingredients(object caster)
{
    return ({ "silver coin"  });
} /* query_locate_ingredients */

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "silver coin";
}

/*
 * Function name:   perform_locate_check
 * Description:     Checks the caller to see if it has reached the desired
 *                  destination.
 * Arguments:       (object) actor - Caster of the spell
 *                  (object) target - Target of the spell
 *                  (object) room - Either object or file_name of the room.
 * Returns:         (int)  0 - Not the desired destination, loop continues with
 *                             the current destinations exits
 *                  (int)  1 - Desired destination, continues with exits
 *                  (int) -1 - Desired destination, ignores exits
 */
public int
perform_locate_check(object actor, object target, object room)
{
    string *herbs;
    
    if (!objectp(room) || !room->query_prop(ROOM_I_IS))
        return 0;
    
    /* There are herbs in the room, lets see if our target is present */
    if (sizeof(herbs = room->query_herb_files()))
    {
        foreach(string herb_file: herbs)
        {
            /* If target is present, stop searching in the rooms beyond this */
            if (herb_file->query_herb_name() != target_locate[actor])
                continue;
            
            if (!herb_file->do_id_check(actor))
                break;
            
            if ((room->calc_pros(actor) - room->calc_cons(actor) -
                (herb_file->query_find_diff() * 10 - 50)) <= 0)
                continue;
            
            return -1;
        }
    }
    
    return 0;
} /* perform_locate_check */

/*
 * Function name:   resolve_locate_spell
 * Description:     Called at the beginning of resolve_spell in order to perform
 *                  spell specific actions.
 * Arguments:       Same as resolve_spell
 * Returns:         Nothing
 */
public void
resolve_locate_spell(object caster, object *targets, int *resist, int result,
                   mapping spell_input)
{
} /* resolve_locate_spell */

/*
 * Function name:   spell_locate_target
 * Description:     Sets the target string so the locate check has a target.
 * Arguments:       (object) actor  - The caster of the spell
 *                  (string) arg    - The arguments used to cast
 * Returns:         (object *) Always empty.
 */
public object *
spell_locate_target(object actor, string arg)
{
    if (!strlen(arg))
    {
        actor->catch_msg("What herb do you wish to locate?\n");
        return ({});
    }
    
    target_locate[actor] = arg;
    
    return spell_target_caster(actor, arg);
} /* spell_locate_target */

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

    caster_message = "You kneel to the ground and call upon Vana, " +
        "the Mistress of Flowers and Song, channelling her love of " +
        "flora to find nearby " +LANG_PWORD(arg)+ ".\n";
    watcher_message = QCTNAME(caster)+ " kneels to the ground and calls " +
           "upon Vana, the Mistress of Flowers and Song, for guidance.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    // Check shadow for chance of detection by Shadow forces
    caster->check_herald_detection();

    setuid();
    seteuid(getuid()); 
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