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
    set_ability_name("tsummon");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(5);
    set_ability_cooldown_time(5);
    set_ability_target(target_actor);
    set_ability_vocal(1);
    set_ability_visual(0);
} /* config_ability */

/*
 * Function name: ability_msg
 * Description:   Displays the ability message.
 */
static void 
ability_msg(object actor, mixed *targets, string arg)
{
    actor->catch_msg("You give off a high-pitched whistle, summoning "
    + capitalize(MANAGER->query_pet_name(actor->query_real_name())) + " to "
    + "your location.\n");
    tell_room(environment(actor), QCTNAME(actor) + " gives off a high-pitched "
    + "whistle.\n", actor, actor);
} /* ability_msg */

/*
 * Function name: resolve_ability
 * Description:   This gets called when the ability is resolved.
 * Returns:       nothing
 */
static void 
resolve_ability(object actor, mixed *items, mixed *targets,
                int *resist, mixed *results)
{
    object  mount;
    int     success,
            house,
            skill,
            matur;
    string  name;
    
    mount   = MANAGER->query_current_pet(actor);
    name    = MANAGER->query_pet_name(actor->query_real_name());
    skill   = actor->query_skill(SS_ANI_HANDL);
    matur   = mount->query_maturity();
    
    if (!objectp(mount))
    {
        actor->catch_msg("Something went wrong.\n");
        return;
    }
    
    if (!(success = MANAGER->query_ability(actor, TSUMMON)))
        success = 1;
    
    success = (((success > 100) ? 100 : success) / 4) +
                (skill / 2) + (matur * 5);
    
    if (matur < 4 && !random(2))
    {
        actor->catch_msg(capitalize(name) + " sprints towards you from not "
        + "too far away. It would appear that as long as "
        + mount->query_pronoun() + " remains " 
        + LANG_ADDART(mount->short()) + " " + mount->query_pronoun() + " will "
        + "always remain in the vicinity.\n");
    }
    else if (!MANAGER->query_ability_success(actor, TSUMMON, success) ||
              mount->query_attack())
    {
        actor->catch_msg(capitalize(name) + " appears to have ignored your "
        + "summons.\n");
        return;
    }
    
    tell_room(environment(mount), "The " + mount->short() + " "
    + mount->query_mm_out() + "\n", 0, mount);
    
    tell_room(environment(actor), capitalize(LANG_ADDART(mount->short()))
    + " " + mount->query_mm_in() + "\n", 0, mount);
    
    MANAGER->add_ability(this_player(), TSUMMON);
    mount->move_living("M", environment(actor), 1, 1);
    MANAGER->add_achievement(this_player(), TDISMISS);
    
    if (MANAGER->query_pet_stay(this_player()))
        MANAGER->set_pet_stay(this_player(), 0);
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
    write("You called for "
    + capitalize(MANAGER->query_pet_name(this_player()->query_real_name()))
    + " just recently, maybe you should wait a while.\n");
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
    write("You called for "
    + capitalize(MANAGER->query_pet_name(this_player()->query_real_name()))
    + " just recently, maybe you should wait a while.\n");
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
check_valid_action(object player, mixed *targets, string arg,
                   int execute)
{
    setuid();
    seteuid(getuid());
    
    string  name;
    object  mount, ship;
    
    mount = MANAGER->query_current_pet(player);
    name  = MANAGER->query_pet_name(player->query_real_name());
    
    if (mount->query_unconcious())
    {
        player->catch_msg("The " + mount->short() + " is unconscious.\n");
        return 0;
    }
    
    if (!MANAGER->load_member(player->query_real_name()) ||
        !strlen(name))
    {
        player->catch_msg("You have no pet to summon.\n");
        return 0;
    }
    
    if (!objectp(mount))
    {
        setuid();
        seteuid(getuid());
    
        mount = clone_object(BEAST + "base/pet_base");
        mount->set_tamer(player->query_real_name());
        mount->set_genus(MANAGER->query_pet_genus(player->query_real_name()));
        mount->configure_genus();
        mount->move(PET_HOUSE);
    }
    
    if (environment(mount) == environment(player))
    {
        player->catch_msg("Just as you were about to summon "
        + capitalize(name) + ", you noticed that " + capitalize(name)
        + " was already present.\n");
        return 0;
    }
    
    if (environment(player)->query_prop(ROOM_I_NO_ALLOW_STEED))
    {
        player->catch_msg("You are unable to summon your pet here.\n");
        return 0;
    }
    /* Allows usage of pet i Moria and similar places.
    if (environment(player)->query_prop(ROOM_I_INSIDE))
    {
        player->catch_msg("You must be outdoors to call for your pet.\n");
        return 0;
    }
    */
    if (objectp(ship = environment(player)->query_ship()) &&
        ship->query_is_at_harbor() < 0 &&
        GENUS->query_pet_habitat(mount->query_genus()) != "air")
    {
        player->catch_msg("You are on a ship, it seems unreasonable to expect "
        + "your pet to swim here.\n");
        return 0;
    }
    
    if (player->query_attack())
    {
        player->catch_msg("You are currently too occupied with combat.\n");
        return 0;
    }

    if (player->query_prop(LIVE_I_STUNNED))
    {
        player->catch_msg("You cannot summon your pet while you are "
        + "stunned.\n");
        return 0;
    }
    
    if ((SPECIALS + "tscout")->query_ability_preparing(player))
    {
        player->catch_msg("You just sent "
        + capitalize(mount->query_real_name()) + " away, don't be in such a "
        + "hurry.\n");
        return 0;
    }

    return 1; 
} /* check_valid_action */

/*
 * Function:    do_ability
 * Description: This is the first function called from the command
 *              soul. For focus, it will handle the different modes.
 */
public int 
do_ability(string arg)
{
    object  mount = MANAGER->query_current_pet(this_player());
    
    if (!IN_ARRAY(TSUMMON, MANAGER->query_achievements(this_player())))
    {
        this_player()->catch_msg("What?\n");
        return 0;
    }
    
    return ::do_ability(arg);
} /* do_ability */