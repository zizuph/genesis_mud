/*
 * /d/Gondor/guilds/rangers/soul/recoded/brew.c
 *
 * This is the brew ability that is used to brew potions. It enhances and
 * replaces the previous <mix> functionality of the Gondor mortar. The
 * ability allows for a craft-like experience to brewing potions, similar
 * to the Smiths.
 *
 * Created by Petros, May 2020
 */

#pragma strict_types

#include "defs.h"

inherit TIMED_ABILITY_LIB;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/std/combat/combat.h"
#include DEBUGGER_LIB

/*
 * Function:    config_ability
 * Description: Configure all the primary attributes of the ability
 *              in this function. Because it uses the standardized
 *              system, this makes it easy to do a balance review.
 */
public void 
config_ability()
{
    ::config_ability();
    set_ability_name("brew");
    set_ability_offensive(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);    
}

/*
 * Function:    ability_msg
 * Description: Customize the message when this ability is
 *              started.
 * Arguments:   actor - the person who started this ability
 *              targets - the list of targets that this ability is aimed at
 *              arg - any additional parameters that were passed to the ability
 */
static void
ability_msg(object actor, mixed * targets, string arg)
{
    setuid();
    seteuid(getuid());
    
    write("You get ready to brew something.\n");
}

/*
 * Function:    resolve_ability
 * Description: resolve_ability
 */
static void
resolve_ability(object actor, mixed * items, mixed * targets, 
                int * resist, mixed * results)
{
    // Execution when ability is complete
}

/*
 * Function:    validate_requirements
 * Description: Function to check all the prerequisites of this ability
 *              These checks are used in both check_valid_action
 *              as well as force fail. (before start, and before execute)
 * Arguments:   player - person executing the special
 * Returns:     0/1 - invalid/valid conditions
 */
public int
validate_requirements(object player)
{
    seteuid(getuid()); 
    int skill = player->query_skill(SS_ALCHEMY);
    if (player->query_attack())
    {
        player->catch_msg("It's a little hard to brew a potion while you're "
            + "otherwise occupied in combat!\n");
        return 0;
    }
    else if (skill < 1)
    {
        player->catch_msg("You really have no clue how to begin. "
            + "Perhaps you should seek training.\n");
        return 0;
    }
    else if (query_ability_active(player))
    {
        hook_already_active(this_object());
        return 0;
    }

    return 1;
}

/*
 * Function:    query_restricted_ability_message
 * Description: Called to inform the player that they are unable to
 *              perform this ability due to other ability being active
 *              or prepared. For example, unable to cast a spell while
 *              another spell is being cast.
 */
public varargs string
query_restricted_ability_message(string ability, object player)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        return "You are too busy brewing something else already!\n";        
    }
    
    return "You are too busy brewing a potion already to " + short_desc 
        + ".\n";    
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    if (!execute && !validate_requirements(player))
    {
        // Only need to validate requirements at the beginning, not at
        // the end.
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

// Hooks

/*
 * Function:    hook_special_complete
 * Description: Customize the message to display to the player when
 *              the special is complete.
 */
public void
hook_special_complete()
{
    write("\nYou feel ready to brew another potion.\n\n");    
}

/*
 * Function:    hook_already_active
 * Description: Customize the message to display to the player when
 *              the special is already in progress and they attempt
 *              it again.
 */
 public void
hook_already_active(object ability)
{
    write("You are already brewing a potion!\n");
}
