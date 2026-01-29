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
#include <terrain.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define SCOUTING "_i_am_scouting"

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
    object pet = MANAGER->query_current_pet(this_player());
    write("You have already sent " + (objectp(pet) ? "the " + pet->short() :
    "your pet") + " out to scout.\n");
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
    object pet = MANAGER->query_current_pet(this_player());
    write("You recently sent " + (objectp(pet) ? "the " + pet->short() :
    "your pet") + " out to scout, " + (objectp(pet) ? pet->query_pronoun() :
    "it") + " does not seem willing to go again so soon.\n");
} /* hook_special_in_cooldown */

/*
 * Function:    hook_no_scry_message
 * Description: When it is not possible to scry, for whatever reason,
 *              this message is given. This applies to no-scry properties
 *              as well as trying to scry a wizard or someone linkdead.
 * Arguments:   actor - person casting the spell
 *              target - the person being scried
 */
public void
hook_no_scry_message(object actor, object target)
{
    object pet = MANAGER->query_current_pet(actor);
    actor->catch_tell("The " + pet->short() + " does not appear to be able to "
    + "track " + capitalize(target->query_real_name()) + ".\n");
} /* hook_scry_no_message */

/*
 * Function:    hook_scry_success
 * Description: When there is a successful scry, a message is prepended
 *              before the room descriptions. This is where you
 *              customize that message.
 * Arguments:   actor - person casting the spell
 *              target - the person being scried
 *              brief  - whether the description will be brief or not
 */
public void
hook_scry_success(object actor, object target, int brief)
{
    object pet = MANAGER->query_current_pet(actor);
    
    if (brief)
    {
        actor->catch_tell(""
        + (objectp(pet) ? capitalize(pet->query_real_name()) : "Your pet")
        + " returns, having scouted out your target's surroundings. "
        + "You guess towards the approximate location.\n");
    }
    else
    {
        actor->catch_tell(""
        + (objectp(pet) ? capitalize(pet->query_real_name()) : "Your pet")
        + " returns, having scouted out your target's surroundings. "
        + "You have a good estimate of the location.\n");
    }
} /* hook_scry_success */

/*
 * Function:    hook_scry_failure
 * Description: When the scry fails because of resistance failure, this
 *              message is given. Also given when the target room doesn't
 *              exist.
 * Arguments:   actor - person casting the spell
 *              target - the person being scried
 */
public void
hook_scry_failure(object actor, object target)
{
    object pet = MANAGER->query_current_pet(actor);
    
    actor->catch_tell("Your "
    + (objectp(pet) ? capitalize(pet->query_real_name()) : "pet")
    + " returns, without finding your target.\n"); 
} /* hook_scry_failure */

/*
 * Function:    hook_notify_been_scried_success
 * Description: A person being scried is notified whenever they are scried.
 *              This message is the one that indicates to them that
 *              the scry was successful.
 * Arguments:   actor - person casting the spell
 *              target - the person being scried
 */
public void
hook_notify_been_scried_success(object actor, object target)
{
    object  pet, *players;
    int     result;
    
    players = filter(all_inventory(environment(target)), &living());
    pet     = MANAGER->query_current_pet(actor);
    
    foreach(object nearby: players)
    {
        result = nearby->resolve_task(TASK_HARD,    ({ SS_AWARENESS, TS_INT }),
                                      pet,          ({ SS_SNEAK, TS_DEX}));
        
        switch(result)
        {
            case  0..15:
            if (nearby == target)
                target->catch_msg("Your senses tell you that someone or "
                + "something is nearby, watching you.\n");
                break;
                
            case 16..45:
            if (nearby == target)
                target->catch_msg("The hairs at the back of your neck rise "
                + "and your instincts scream that you are being hunted, a "
                + "predator is on the prowl.\n");
            else
                nearby->catch_msg("You notice something moving in your "
                + "peripheral vision, but it is gone before you manage to "
                + "react. The unknown presence appeared to have been focused "
                + "on " + QTNAME(target) + ".\n");
                break;
                
            case 46..100:
            nearby->catch_msg("You notice " + LANG_ADDART(pet->short()) + " "
            + "prowling in the vicinity, its focus solely on "
            + (nearby == target ? "you" : QTNAME(target)) + ". The "
            + pet->short() + " soon " + pet->query_mm_out() + ".\n");
                break;
                
            default:
                break;
        }
    }
} /* hook_notify_been_scried_success */

/*
 * Function:    hook_notify_been_scried_failure
 * Description: A person being scried is notified whenever they are scried.
 *              This message is the one that indicates to them that
 *              the scry was not successful.
 * Arguments:   actor - person casting the spell
 *              target - the person being scried
 */
public void
hook_notify_been_scried_failure(object actor, object target)
{
    /* No message if the pet fails to find the target, as it is highly unlikely
     * that the target knows about it if such were the case.
     */
} /* hook_notify_been_scried_failure */


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
    set_ability_name("tscout");
    set_ability_offensive(0);
    set_ability_hasted(0);
    set_ability_prep_time(15);
    set_ability_cooldown_time(30);
    set_ability_target(target_one_distant_known_living);
    set_ability_target_verify(0);
    set_ability_vocal(1);
    set_ability_visual(0);
} /* config_ability */

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    /* Minimum 10% fatigue drain */
    int fatigue = max(player->query_max_fatigue() - player->query_stat(SS_DEX),
                      player->query_max_fatigue() / 10);
    
    if (player->query_fatigue() > fatigue)
    {
        /* Reduce pet fatigue value */
        player->add_fatigue(-fatigue);
        return;
    }
    
    /* Reduce health if fatigue is too low */
    fatigue -= player->query_fatigue();
    player->set_fatigue(0);
    player->heal_hp(-fatigue);
    player->tell_watcher("The strain of scouting appears to have been draining "
    + "to " + QTNAME(player) + ".\n");
} /* apply_costs_to_player */

/*
 * Function:    query_provide_brief_description
 * Description: Sometimes scrying should not show the full description.
 *              Instead, it will only show the brief description of
 *              the room. This function determines whether it is brief
 *              or not. By default, it's a 50% chance of it being brief.
 *              You should customize it to suit your needs.
 * Arguments:   same as config_spell
 */
public int
query_provide_brief_description(object actor, object * targets, int * resist,
                                int result)
{
    // 50% chance of getting a brief description
    return random(2);
} /* query_provide_brief_description */

/*
 * Function name: ability_msg
 * Description:   Displays the ability message, moves the pet to pet_house.
 */
static void 
ability_msg(object actor, mixed *targets, string arg)
{
    object pet = MANAGER->query_current_pet(actor);
    pet->move_living("M", PET_HOUSE, 0, 0);
    pet->add_prop(SCOUTING, 1);
    actor->catch_msg("You send " + capitalize(pet->query_real_name()) + " out "
    + "to scout for " + capitalize(targets[0]->query_real_name()) + "'s "
    + "location.\n");
    tell_room(environment(actor), QCTNAME(actor) + " sends " + QTNAME(pet)
    + " out to scout.\n", actor, actor);
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
    object  target = targets[0],
            target_room,
            pet = MANAGER->query_current_pet(actor);
    
    pet->remove_prop(SCOUTING, 1);
    pet->move_living("M", environment(actor), 0, 0);
    actor->tell_watcher(QCTNAME(pet) + " returns from having been out " +
    "scouting.\n");

    // Apply any costs to player, such as fatigue
    apply_costs_to_player(pet);
    
    if (target == actor)
    {
        actor->do_glance();
        return;
    }
    
    if (target->query_wiz_level() || target->query_linkdead())
    {
        // Not allowed to scry wizards or linkdead people
        hook_no_scry_message(actor, target);
        return;
    }
    
    target_room = environment(target);

    // If it's not a valid room, fail.
    if (!objectp(target_room) || (target_room->query_ship() &&
        GENUS->query_pet_habitat(pet->query_genus()) != "air") ||
        ((target_room->terrain_includes_any(TERRAIN_UNDERWATER) ||
        target_room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) &&
        GENUS->query_pet_habitat(pet->query_genus()) != "water"))
    {
        hook_scry_failure(actor, target);
        hook_notify_been_scried_failure(actor, target);
        return;
    }

    // If the target or room is no scry, fail.
    if (target->query_prop(LIVE_M_NO_SCRY) ||
        target_room->query_prop(ROOM_M_NO_SCRY))
    {
        hook_no_scry_message(actor, target);
        return;
    }

    hook_notify_been_scried_success(actor, target);
    
    if (query_provide_brief_description(actor, targets, resist, results[0]))
    {
        hook_scry_success(actor, target, 1);
        actor->catch_tell(capitalize(target_room->short()) + ".\n");
        actor->catch_tell(target_room->exits_description());
    }
    else
    {
        hook_scry_success(actor, target, 0);
        actor->catch_tell(capitalize(target_room->short()) + ".\n");
        actor->catch_tell(target_room->long());
    }

    object * inv = all_inventory(environment(target)) - ({ target });
    inv = filter(inv, &->check_seen(target));
    
    object * live = FILTER_LIVE(inv);
    object * dead = FILTER_DEAD(inv);
    
    if (sizeof(dead))
        actor->catch_msg(capitalize(COMPOSITE_DEAD(dead)) + ".\n");
    
    if (sizeof(live))
        actor->catch_msg(capitalize(COMPOSITE_LIVE(live)) + ".\n");
    
    return;
} /* resolve_ability */

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
check_valid_action(object actor, mixed *targets, string arg,
                   int execute)
{
    object  mount;
    
    mount   = MANAGER->query_current_pet(actor);
    
    if (mount->query_unconcious())
    {
        actor->catch_msg("The " + mount->short() + " is unconscious.\n");
        return 0;
    }
    
    if (actor->query_attack())
    {
        actor->catch_msg("You are currently too occupied with combat.\n");
        return 0;
    }

    if (mount->query_prop(LIVE_I_STUNNED))
    {
        actor->catch_msg("Your pet is stunned and unable to scout.\n");
        return 0;
    }
    
    if (actor->query_prop(LIVE_I_STUNNED))
    {
        actor->catch_msg("You cannot send your pet to scout while you are "
        + "stunned.\n");
        return 0;
    }

    if (mount->query_driver())
    {
        actor->catch_msg("You must dismount the " + mount->short() + " "
        + "before you can send it to scout.\n");
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
    object  mount, ship;
    
    mount = MANAGER->query_current_pet(this_player());
    
    if (!IN_ARRAY(TSCOUT, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (GENUS->query_genus_rideable(mount))
    {
        notify_fail("Your pet does not know how to perform such a feat, it is "
        + "more suitable as a mount than a scout.\n");
        return 0;
    }
    
    if ((!objectp(mount) || (environment(mount) != environment(this_player())))
        && !mount->query_prop(SCOUTING))
    {
        notify_fail("You might wish to summon your pet before trying to send "
        + "it out to scout.\n");
        return 0;
    }
    
    if (objectp(ship = environment(this_player())->query_ship()) &&
        ship->query_is_at_harbor() < 0 &&
        GENUS->query_pet_habitat(mount->query_genus()) != "air")
    {
        notify_fail("You are on a ship, it seems unreasonable to expect your "
        + "pet to swim from here.\n");
        return 0;
    }
    
    return ::do_ability(arg);
} /* do_ability */