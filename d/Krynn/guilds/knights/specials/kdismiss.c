/*
 * /d/Krynn/guilds/knights/specials/kdismiss.c
 *
 * This is the dismiss ability for Knights. Using this, they can dismiss
 * their mounts to an idle room, and can summon them later.
 *
 * Created by Petros, October 2008
 */
 
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";
inherit KNIGHT_UTILITY;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define HORSE_ROOM (VROOM + "horse_idle_room")

public void config_ability()
{
    ::config_ability();
    set_ability_name("kdismiss");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(0);
    set_ability_vocal(1);
    set_ability_visual(0);    
    set_ability_target(target_actor);    
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("You release the reigns of your steed and signal it "
        + "to return home.\n");
    tell_room(environment(actor), QCTNAME(actor) + " releases the reigns "
        + "of " + HIS(actor) + " steed and gives it a command.\n", actor);
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object horse, room;
    
    horse = query_solamnian_steed(actor);
    if (!objectp(horse))
    {
        return;
    }
    
    room = environment(actor);    

    tell_room(environment(horse), "The "+horse->query_short()+" gallops off.\n",
	      horse);
    tell_room(HORSE_ROOM, capitalize(LANG_ADDART(horse->query_short()))+ " arrives.\n",
	      horse);
    horse->do_unlead(actor, 1);
    horse->move_living("M", HORSE_ROOM, 1, 1);

}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already dismissing your steed!\n");
}

public void
hook_special_in_cooldown()
{
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
    object horse, room;
    mixed * riders;
    
    horse = query_solamnian_steed(player);
    if (!objectp(horse))
    {
        player->catch_msg("You have no steed to dismiss!\n");
        return 0;
    }

    room = environment(player);
    if (environment(horse) != environment(player))
    {
        player->catch_msg("Your steed is not present for you to dismiss!\n");
        return 0;
    }
    
    if (player->query_attack())
    {
        player->catch_msg("You cannot dismiss your steed while "
            + "fighting.\n");
        return 0;
    }

    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot dismiss your steed while "
            + "stunned.\n");
        return 0;
    }

    if (horse->query_attack() || horse->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You can't dismiss your steed while it is in "
            + "combat.\n");
        return 0;
    }

    if ((riders = horse->query_riders()) && (sizeof(riders)))
    {
        player->catch_msg("You can't dismiss your steed while it has a "
            + "rider on it.\n");
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}
