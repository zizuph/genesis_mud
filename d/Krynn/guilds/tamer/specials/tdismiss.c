/*
 *
 * Created by Carnak, 
 */
 
#pragma strict_types

#include "../defs.h"

inherit "/d/Genesis/specials/timed_ability";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void
config_ability()
{
    ::config_ability();
    set_ability_name("tdismiss");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(1);
    set_ability_cooldown_time(0);
    set_ability_vocal(1);
    set_ability_visual(0);    
    set_ability_target(target_actor);    
} /* config_ability */

/*
 * Function name: ability_msg
 * Description:   Displays the ability message.
 */
static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object  mount;
            
    mount   = MANAGER->query_current_pet(actor);
    
    actor->catch_msg("You dismiss the " + mount->short() + ".\n");
    tell_room(environment(actor), QCTNAME(actor) + " whispers to the "
    + mount->short() + ".\n", actor);
} /* ability_msg */

/*
 * Function name: resolve_ability
 * Description:   This gets called when the ability is resolved.
 * Returns:       nothing
 */
static void 
resolve_ability(object actor, mixed * items, mixed * targets, int * resist,
                mixed * results)
{
    object  mount;
    
    mount   = MANAGER->query_current_pet(actor);
    
    if (mount->query_attack())
    {
        tell_room(environment(actor), "The " + mount->short() + " retreats "
        + "from combats.\n", 0, mount);
        mount->stop_fight(mount->query_attack());
    }
    
    tell_room(environment(mount), "The " + mount->short() + " "
    + mount->query_mm_out() + "\n", mount);
    tell_room(PET_HOUSE, capitalize(LANG_ADDART(mount->short())) + " "
    + mount->query_mm_in() + "\n", mount);
    
    MANAGER->add_ability(this_player(), TDISMISS);
    mount->move_living("M", PET_HOUSE, 1, 1);
} /* resolve_ability */

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
} /* hook_special_complete */

/*
 * Function name: hook_already_active
 * Description:   Called if the player attempts to use the special when active.
 * Returns:       nothing
 */
public void
hook_already_active(object ability)
{
    write("You are already dismissing your pet.\n");
} /* hook_already_active */

/*
 * Function name: hook_special_in_cooldown
 * Description:   This gets called if the player attempts to use the ability
 *                when it is in cooldown.
 * Returns:       nothing
 */
public void
hook_special_in_cooldown()
{
} /* hook_special_in_cooldown */

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
    object *enemies,
            mount, 
            ship;
    string  name;
    
    mount   = MANAGER->query_current_pet(player);
    name    = MANAGER->query_pet_name(player->query_real_name());
    
    if (!IN_ARRAY(TDISMISS, MANAGER->query_achievements(player)))
    {
        player->catch_msg("What?\n");
        return 0;
    }
    
    if (mount->query_unconcious())
    {
        this_player()->catch_msg("The " + mount->short() + " is "
        + "unconscious.\n");
        return 0;
    }
    
    if (!MANAGER->load_member(this_player()->query_real_name()) ||
        !strlen(name) || !objectp(mount))
    {
        player->catch_msg("You have no pet to dismiss.\n");
        return 0;
    }
    
    if (environment(mount) != environment(player))
    {
        player->catch_msg("Your pet is not present.\n");
        return 0;
    }
    
    enemies = filter(all_inventory(environment(mount)),
              &operator(==)(mount) @ &->query_attack());
    
    if (sizeof(enemies))
    {
        player->catch_msg(capitalize(name) + " is under attack, and unable to "
        + "retreat.\n");
        return 0;
    }

    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot dismiss your pet while stunned.\n");
        return 0;
    }

    if (mount->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("Your pet is stunned and unable to retreat.\n");
        return 0;
    }
    
    if (environment(player)->query_prop(ROOM_I_INSIDE))
    {
        player->catch_msg("You must be outdoors to dismiss your pet.\n");
        return 0;
    }

    if (mount->query_driver())
    {
        player->catch_msg("You must dismount the " + mount->short() + " "
        + "before you dismiss it.\n");
        return 0;
    }
    
    if (objectp(ship = environment(player)->query_ship()) &&
        ship->query_is_at_harbor() < 0 &&
        GENUS->query_pet_habitat(mount->query_genus()) != "air")
    {
        player->catch_msg("You are on a ship, it seems unreasonable to expect "
        + "your pet to swim from here.\n");
        return 0;
    }

    if (player->query_prop(LIVE_O_STEED) == mount)
        player->dismount();
    
    return 1; 
} /* check_valid_action */
