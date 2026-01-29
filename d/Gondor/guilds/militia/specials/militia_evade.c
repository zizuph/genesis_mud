/*
 * /d/Gondor/guilds/militia/specials/militia_evade.c
 *
 * This is the militia evade ability that is used by the command
 * soul. This merely starts the evade portion, and allows the evade
 * object in the Militia member to function.
 *
 * Created by Petros, September 2008
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

public void config_ability()
{
    ::config_ability();
    set_ability_name("evade");
    set_ability_offensive(0);
    set_ability_prep_time(18);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);
    
    // Jab cannot be used at the same time as Evade
    add_ability_restriction(JAB_ABILITY);    
}

public void
remove_existing_militia_evades(object actor)
{
    object * evades;

    if (!actor->has_evade_shadow())
    {
        return;
    }

    // Remove all existing evades first
    evades = actor->query_evade_effects() + all_inventory(actor);
    evades = filter(evades, &->is_militia_evade());
    if (sizeof(evades))
    {
        evades->remove_object();
    }
}

static void ability_msg(object actor, mixed * targets, string arg)
{
    object evade_obj;
    
    setuid();
    seteuid(getuid());
    
    write("You watch your enemy closely, ready to evade his attacks.\n");
    
    // Remove all existing evades first
    remove_existing_militia_evades(actor);
    
    evade_obj = clone_object(EVADE_OBJ);
    evade_obj->set_effect_caster(actor);
    evade_obj->set_effect_target(actor);
    evade_obj->move(actor, 1);
    evade_obj->start();
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    // When the ability executes, we remove all the militia
    // evade objects from the person
    remove_existing_militia_evades(actor);    
}

public void
hook_special_complete()
{
    write("\nYou feel ready to attempt evasive maneuvers " +
        "again.\n\n");    
}

public void
hook_already_active(object ability)
{
    write("You are already evading attacks!\n");
}

/*
 * Function name: validate_requirements
 * Description  : Function to check all the prerequisites of charge
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_requirements(object player)
{
    seteuid(getuid()); 
    int skill;
    
    skill = player->query_skill(SS_MILITIA);

    if (!player->query_attack())
    {
        player->catch_msg("You aren't in combat!\n");
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

public varargs string
query_restricted_ability_message(string ability, object player)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        return "You are too busy evading attacks right now.\n";        
    }
    
    return "You are too busy evading attacks to " + short_desc + ".\n";    
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
    object enemy;
    object * enemies;
    
    if (!execute && !validate_requirements(player))
    {
        // Only need to validate requirements at the beginning, not at
        // the end.
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}


