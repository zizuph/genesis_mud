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

#define SCOUTING "_i_am_scouting"

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
    object pet = MANAGER->query_current_pet(this_player());
    
    pet->move_living("M", environment(this_player()), 0, 0);
    pet->remove_prop(SCOUTING);
    
    write("The " + pet->query_nonmet_name() + " has successfully delivered "
    + "your message.\n");
} /* hook_special_complete */

public void
hook_already_active(object ability)
{
    object pet = MANAGER->query_current_pet(this_player());
    
    write("You have already sent " + (objectp(pet) ? "the "
    + pet->query_nonmet_name() : "your pet") + " out to deliver a message.\n");
}

public void
hook_special_in_cooldown()
{
    write("It is already out delivering a message, please be patient.\n");
}

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
    set_ability_prep_time(3);
    set_ability_cooldown_time(2);
    set_ability_target(target_one_distant_living);
    set_ability_target_verify(0);
    set_ability_vocal(1);
    set_ability_visual(1);
} /* config_ability */

/*
 * Function name: ability_msg
 * Description:   Displays the ability message, moves the pet to pet_house.
 */
static void 
ability_msg(object actor, mixed *targets, string arg)
{
    object pet = MANAGER->query_current_pet(actor);
    
    actor->catch_msg("You send " + capitalize(pet->query_real_name()) + " out "
    + "to deliver a message to " + capitalize(targets[0]->query_real_name())
    + ".\n");
    tell_room(environment(actor), QCTNAME(actor) + " sends " + QTNAME(pet)
    + " to deliver a message.\n", actor, actor);
    
    pet->move_living("M", PET_HOUSE, 0, 0);
    pet->add_prop(SCOUTING, 1);
} /* ability_msg */

static void
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *results)
{
    object  target = targets[0], message,
            pet = MANAGER->query_current_pet(actor);
    
    pet->move_living("X", PET_HOUSE, 0, 0);
    
    message = pet->query_prop("_tamer_message_ob");
    pet->remove_prop("_tamer_message_ob");
    message->move(target, 1);
    
    target->catch_msg(capitalize(LANG_ADDART(pet->query_nonmet_name())) + " "
    + pet->query_mm_in() + "\nThe " + pet->query_nonmet_name() + " drops "
    + LANG_ADDART(message->short()) + " at your feet, you retrieve it before "
    + "the " + pet->query_nonmet_name() + " " + pet->query_mm_out() + "\n");
    tell_room(environment(target), ""
    + capitalize(LANG_ADDART(pet->query_nonmet_name())) + " "
    + pet->query_mm_in() + "\nThe " + pet->query_nonmet_name() + " drops "
    + LANG_ADDART(message->short()) + " at " + QTNAME(actor) + "'s feet. "
    + QCTNAME(actor) + " picks up the " + message->short() + " before "
    + "the " + pet->query_nonmet_name() + " " + pet->query_mm_out() + "\n");
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
check_valid_action(object actor, mixed *targets, string arg, int execute)
{
    setuid();
    seteuid(getuid());
    
    object  mount;
    
    mount   = MANAGER->query_current_pet(actor);
    
    if (mount->query_unconcious())
    {
        actor->catch_msg(QCTNAME(mount) + " is unconscious.\n");
        return 0;
    }
    
    if (actor->query_attack())
    {
        actor->catch_msg("You are currently too occupied with combat.\n");
        return 0;
    }

    if (mount->query_prop(LIVE_I_STUNNED))
    {
        actor->catch_msg("Your pet is stunned and unable to deliver a message."
        + "\n");
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
        actor->catch_msg("You must dismount " + QTNAME(mount) + " before you "
        + "can send it away.\n");
        return 0;
    }
    
    if (!objectp(mount->query_prop("_tamer_message_ob")))
    {
        actor->catch_msg("You almost sent your pet out without a message.\n");
        return 0;
    }
    
    if (targets[0] == actor)
    {
        actor->catch_msg("Why would you send yourself a message?\n");
        return 0;
    }
    
    if (environment(targets[0]) == environment(actor))
    {
        actor->catch_msg("Why not just tell them in person?\n");
        return 0;
    }
    
    if (targets[0]->query_wiz_level() || targets[0]->query_linkdead())
    {
        // Not allowed to annoy wizards
        actor->catch_msg("You would not risk the life of your companion in "
        + "in the vastness of the void. You decide not to send the message.\n");
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
    setuid();
    seteuid(getuid());
    
    object  mount, ship;
    
    mount = MANAGER->query_current_pet(this_player());
    
    if (!IN_ARRAY(TSCOUT, MANAGER->query_achievements(this_player())))
    {
        notify_fail("What?\n");
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
        + "pet to brave the sea.\n");
        return 0;
    }
    
    return ::do_ability(arg);
} /* do_ability */