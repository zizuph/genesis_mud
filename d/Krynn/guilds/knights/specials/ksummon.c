/*
 * /d/Krynn/guilds/knights/specials/ksummon.c
 *
 * This is the summon ability for Knights to retrieve their mounts. This
 * is to be used in conjunction with kdismiss.
 *
 * Created by Petros, October 2008
 *
 * Removed the illogical restriction of not being able to call your
 * steed while in combat - Arman 2017
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
    set_ability_name("ksummon");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(8);
    set_ability_cooldown_time(0);
    set_ability_target(target_actor);    
    set_ability_vocal(1);
    set_ability_visual(0);
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg("You give a shrill whistle.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gives a shrill "
        + "whistle.\n", actor, actor);
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object horse, room;
    object * riders;
    
    horse = query_solamnian_steed(actor);
    if (!objectp(horse))
    {
        return;
    }
    
    room = environment(actor);

    // Handle the case if there are already riders on the horse
    if ((riders = horse->query_riders()) && (sizeof(riders)))
    {
        riders->catch_msg("You see " + QTNAME(horse) + " perk up "
            + horse->query_possessive() + " ears and immediately "
            + "tries to buck you off " + horse->query_possessive()
            + " back.\n");
        horse->dismount_all();
    }
    
    tell_room(environment(horse), "The " + horse->query_short() 
        + " gallops off.\n", 0, horse);
    tell_room(room, capitalize(LANG_ADDART(horse->query_short()))
        + " arrives.\n", 0, horse);
    horse->move_living("M", room, 1, 1);
}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already summoning your steed!\n");
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
        player->catch_msg("You have no steed to summon!\n");
        return 0;
    }

    room = environment(player);
    if (environment(horse) == room)
    {
        player->catch_msg("Your steed is already here!\n");
        return 0;
    }

    if (room->query_prop(ROOM_I_NO_ALLOW_STEED))
    {
        player->catch_msg("You are unable to summon your steed here.\n");
        return 0;
    }

/*
    if (player->query_attack())
    {
        player->catch_msg("You cannot summon your steed while fighting.\n");
        return 0;
    }
*/

    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot summon your steed while stunned.\n");
        return 0;
    }

    if (horse->query_attack() || horse->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You steed is unable to respond to your summons.\n");
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}
