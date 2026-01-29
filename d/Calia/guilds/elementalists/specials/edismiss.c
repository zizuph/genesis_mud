/*
 * Dismiss Elemental from Room
 *
 * This is the dismiss ability (not spell) to send a person's already
 * summoned elemental away, who happens to be in the same room at the
 * moment.
 *
 * This ability is modeled after the Knight kdismiss command.
 *
 * Created by Petros, February 2013
 */
 
#pragma strict_types

#include "../defs.h"

inherit "/d/Genesis/specials/timed_ability";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define ELEMENTAL_ROOM (ELEMENTALIST_TEMPLE + "elemental_idle_room")

public void config_ability()
{
    ::config_ability();
    set_ability_name("edismiss");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(0);
    set_ability_vocal(1);
    set_ability_visual(0);    
    set_ability_target(target_actor);    
}

/*
 * Function:    query_elemental_summoning
 * Description: Returns the currently summoned elemental
 */
public object
query_elemental_summoning(object actor)
{
    object * choma_objects = GUILD_MANAGER->get_existing_choma_objects(actor);
    if (!sizeof(choma_objects))
    {
        return 0;
    }
    
    return choma_objects[0]->query_summoned_object();
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object summoned = query_elemental_summoning(actor);
    actor->catch_msg("You release " + QTNAME(summoned) + " and signal it "
        + "to return home.\n");
    tell_room(environment(actor), QCTNAME(actor) + " releases the control "
        + "of " + QTNAME(summoned) + " and gives it a command.\n", actor);
}

static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object elemental = query_elemental_summoning(actor);
    if (!objectp(elemental))
    {
        return;
    }
    
    elemental->move_living("X", ELEMENTAL_ROOM, 1, 1);

}

public void
hook_special_complete()
{
}

public void
hook_already_active(object ability)
{
    write("You are already dismissing your elemental!\n");
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
    object elemental = query_elemental_summoning(player);
    if (!objectp(elemental))
    {
        player->catch_msg("You have not invoked the gift of choma!\n");
        return 0;
    }

    object room = environment(player);
    if (environment(elemental) != environment(player))
    {
        player->catch_msg(QCTNAME(elemental) + " is not present for you to dismiss!\n");
        return 0;
    }
    
    if (player->query_attack())
    {
        player->catch_msg("You cannot dismiss " + QTNAME(elemental) 
            + " while in combat.\n");
        return 0;
    }

    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot dismiss " + QTNAME(elemental) 
            + " while stunned.\n");
        return 0;
    }

    if (elemental->query_attack() || elemental->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You can't dismiss " + QTNAME(elemental) 
            + " while it is in combat.\n");
        return 0;
    }

    if (elemental->query_has_riders())
    {
        player->catch_msg("You can't dismiss " + QTNAME(elemental) 
            + " while it has riders.\n");
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}
