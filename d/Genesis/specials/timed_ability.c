/*
 * /d/Genesis/specials/timed_ability.c
 *
 * Timed special
 * 
 * This module provides support for non-spell abilities that need explicit
 * alarms called out.  Alarms for both preparation and cooldown are added
 * at:
 *     time / 2 + random (time / 2) + random (time / 2) seconds
 * 
 * This method of randomizing the timer is designed to make things more
 * interesting. One can set the prep time and the cooldown separately in
 * the base ability functions set_ability_prep_time and 
 * set_ability_cooldown_time. If simply setting set_ability_time, then
 * the base ability module will handle the split between the two.
 * 
 * One also has the ability to set whether the ability should be hasted
 * or not. If so, the ability's prep and cooldown times will be modified
 * by LIVE_I_QUICKNESS.
 *
 * set_ability_hasted(int)
 *     Set whether LIVE_I_QUICKNESS affects the speed of this ability
 *     Default: 1
 * 
 * Created May 2008 by Novo
 * Adapted for Prep and Cooldown times by Petros, October 2008
 * 
 * - Added hook_special_preparation_complete to support actions that need to be
 *   performed right before execution. Petros, November 2008
 *
 * Modified 2019-06-10 by Carnak:
 *  - Modification added to cap the effect of haste on cooldown and prep time,
 *    haste bugs could result in instant activation at 501 haste. The new cap
 *    is at 300 haste which results in an average: ability_time / 2.5
 *  - Added a check for query_ability_hasted as there was none previously.
 *
 * Modified 2021-02-17 by Carnak:
 * - Changed the ability duration based on two handed combat to balance the
 *   one-handed vs two-handed weapon functionality in the game.
 */

#include "defs.h"

inherit ABILITY_LIB;

#include <stdproperties.h>
#include <ss_types.h>
#include <comb_mag.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

static int  Ability_haste,          /* Is this ability affected by haste? */
            Ability_dual_wield;     /* True if affected by two-handed combat */
static mapping prepare_alarms = ([ ]);
static mapping cooldown_alarms = ([ ]);
static mapping two_handed_combat = ([ ]);

// Defines
#define LIVE_O_ACTION            "_live_o_action_"

// Prototypes
public void     set_ability_pending(object actor, object room, int set);

public void set_ability_hasted(int hasted)
{
    Ability_haste=hasted;
}

public int query_ability_hasted()
{
    return Ability_haste;
}

/*
 * Function name:   set_ability_dual_wield
 * Description:     Set whether or not the ability is affected by two handed combat.
 * Arguments:       1. (int) True if the ability is affected by two handed combat
 * Returns:         Nothing
 */
public void
set_ability_dual_wield(int dual_wield)
{
    Ability_dual_wield = dual_wield;
} /* set_ability_dual_wield */

/*
 * Function name:   query_ability_dual_wield
 * Description:     By default, just returns the value specified in
 *                  set_ability_offensive. However, this can be
 *                  overridden to take into account the targets and
 *                  determine whether to be offensive or not.
 * Arguments:       1. (mixed *) (Optional) targets
 * Returns:         Nothing
 */
public varargs int
query_ability_dual_wield(mixed * targets = 0)
{
    return Ability_dual_wield;
} /* query_ability_dual_wield */

public void
restart_npc_special(object actor, string arg)
{
}

public void 
hook_special_complete()
{
    write("You feel ready to "+short()+" again.\n");
}

public void
hook_special_in_cooldown()
{
    write("You do not feel ready to " + short() + " again.\n");
}

public void
hook_special_preparation_complete()
{
}

public int
bouncing_during_cooldown(object actor, mixed * targets, string arg)
{
    // We detect bouncing during cooldown by comparing the location
    // of the attacker and the target with the original location
    // where the special was executed.
    object oldroom, attackerroom, targetroom, target;
    
    oldroom = query_ability_startloc(actor);
    if (!oldroom)
    {
        // If the start location is not set, we can't determine
        // bouncing. It becomes unset also if the cooldown time has
        // already been extended once.
        return 0;
    }
    
    attackerroom = environment(actor);

    foreach (mixed arrayitem : targets)
    {
        if (pointerp(arrayitem) && sizeof(arrayitem) > 0)
        {
            target = arrayitem[0];
        }
        else if (objectp(arrayitem))
        {
            target = arrayitem;
        }
        else
        {
            continue;
        }
        if (!objectp(target))
        {
            // When target is dead, we don't consider it.
            continue;
        }
        
        targetroom = environment(target);
        if (targetroom == oldroom
            && attackerroom != oldroom)
        {
            // This means that the target hasn't moved, but the attacker
            // has. This is the definition of bouncing for abilities.
            // Until we have a way to detect actual bouncing moves, this
            // will have to do.
            return 1;
        }
    }
    
    // If we get here, then all conditions are right. cooldown can
    // be properly ended.
    return 0;
}

/*
 * Function:    notify_npc_cooldown_complete
 * Description: This is called by cooldown_ability when the ability has 
 *              actually finished its cooldown.
 *              It will primarily be used to help the test rooms to
 *              coordinate the next ability to use for the npcs. This
 *              is NOT called for normal players.
 */
public void
notify_npc_cooldown_complete(object player, string arg)
{
}

/*
 * Function:    cooldown_ability
 * Description: Function that gets called when the ability has completed
 *              its cooldown period.
 * Arguments:   actor - the player executing the ability
 *              targets - the targets of the ability
 *              arg - string passed in for the ability
 * Returns:     nothing
 */
static nomask
void cooldown_ability(object actor, mixed * targets, string arg)
{
    if (!objectp(actor))
    {
        m_delkey(cooldown_alarms, 0);
        return;
    }
    
    object tp = this_player();
    set_this_player(actor);
    // Remove the alarm entry from the mapping
    if (IN_ARRAY(actor, m_indices(cooldown_alarms)))
    {
        m_delkey(cooldown_alarms, actor);
    }
    
    if (bouncing_during_cooldown(actor, targets, arg))
    {
        set_ability_startloc(actor, 0);
        float cooldown_time = itof(query_ability_time());
        cooldown_alarms[actor] = set_alarm(cooldown_time, 0.0, 
                                           &cooldown_ability(actor, targets, arg));
        send_debug_message("timed_ability", "Bouncing detected. Adding an additional "
                         + ftoa(cooldown_time) + " seconds for cooldown.");
    }
    else
    {
        hook_special_complete();
        if (actor->query_npc())
        {
            restart_npc_special(actor, arg);
            // NPCs need to know when the special has executed. This is especially
            // useful for test purposes, so that they can execute the next
            // ability, such as for spells.
            set_alarm(0.0, 0.0, &notify_npc_cooldown_complete(actor, arg));
        }
    }
    set_this_player(tp);
}

/*
 * Function:    notify_npc_preparation_complete
 * Description: This is called by prepare_ability when the ability has 
 *              actually finished its preparation, and executed the special.
 *              It will primarily be used to help the test rooms to
 *              coordinate the next ability to use for the npcs. This
 *              is NOT called for normal players.
 */
public void
notify_npc_preparation_complete(object player, string arg)
{
}

/*
 * Function:    prepare_ability
 * Description: This is the function called at the end of the prep time
 *              for the ability. It will make the calls to execute the
 *              ability and set up the cooldown time, if applicable.
 * Arguments:   actor - player executing the ability
 *              targets - targets of the ability
 *              arg - string passed in for the ability
 * Returns:     nothing
 */
static nomask 
void prepare_ability(object actor, mixed * targets, string arg)
{
    object tp = this_player();

    if (!objectp(actor))
		return;

    set_this_player(actor);
    
    /*
     * This functionality was added so that we can prevent users
     * from abusing the boost they get from dual wielding.
     */
    if (floatp(two_handed_combat[actor]) &&
        two_handed_combat[actor] > 0.0 &&
        sizeof(actor->query_weapon(-1)) < 2)
    {
        if (IN_ARRAY(actor, m_indices(prepare_alarms)))
        {
            remove_alarm(prepare_alarms[actor]);
        }
        prepare_alarms[actor] = set_alarm(two_handed_combat[actor], 0.0, 
                                      &prepare_ability(actor,targets,arg));
        send_debug_message("timed_ability_2H", "Ability time extended with "
        + ftoa(two_handed_combat[actor]) + " seconds due to changing from "
        + "two-handed combat.");
        two_handed_combat[actor] = 0.0;
        return;
    }
    
    hook_special_preparation_complete();
    set_ability_pending(actor, 0, 0); // backwards compatibility
    if (execute_ability(actor, targets, arg)
        && query_ability_cooldown_time())
    {
        float speed, time;

        speed = max(2.0, actor->query_speed(5.0));
        time  = itof(query_ability_cooldown_time()) / 2.0;
        
        if (query_ability_hasted())
            time = time * speed / 5.0;
        
        time += (rnd() * time) + (rnd() * time);
        
        /* Making the ability time scale based on two-handed combat, as
         * seen in the function cb_calc_attackuse.
         */
        if (query_ability_dual_wield() && sizeof(actor->query_weapon(-1)) > 1)
        {
            float   old_time = time;
            int     extra = actor->query_skill(SS_2H_COMBAT);
            extra = extra > 20 ? extra / 2 : extra - 20;
            time = time * 100.0 / (100.0 + itof(extra));
            send_debug_message("timed_ability_2H", "Old time: " + ftoa(old_time)
            + " New time: " + ftoa(time));
        }
        
        if (IN_ARRAY(actor, m_indices(cooldown_alarms)))
        {
            remove_alarm(cooldown_alarms[actor]);
        }
        cooldown_alarms[actor] = set_alarm(time, 0.0, &cooldown_ability(actor, targets, arg));
        send_debug_message("timed_ability", "Ability cooling for "
                         + ftoa(time) + " seconds.");
        
        // We set the ability start location again to verify bouncing in
        // cooldown_ability
        set_ability_startloc(actor, environment(actor));
    }
    else
    {
        hook_special_complete();
        if (actor->query_npc())
        {
            restart_npc_special(actor, arg);
        }
    }        
    
    // Remove the alarm entry from the mapping
    if (IN_ARRAY(actor, m_indices(prepare_alarms)))
    {
        m_delkey(prepare_alarms, actor);
    }
    
    if (actor->query_npc())
    {
        // NPCs need to know when the special has executed. This is especially
        // useful for test purposes, so that they can execute the next
        // ability, such as for spells.
        set_alarm(0.0, 0.0, &notify_npc_preparation_complete(actor, arg));
    }
    
    set_this_player(tp);
}

/*
 * Function:    notify_prep_time
 * Description: This is a hook that abilities can use to know how long
 *              the prep time is before execution. A common usage of
 *              this may be to provide interim messages for long
 *              delays.
 * Arguments:   prep_time - the time before preparation and execution
 * Returns:     nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
}

/*
 * Function:    schedule_ability
 * Description: This is the first scheduling function called by do_ability
 *              It sets up the prepare_alarm if applicable.
 * Arguments:   actor - The person executing the ability
 *              targets - the targets of the ability
 *              arg - string passed by player for arguments
 * Returns:     nothing
 */
static nomask
void schedule_ability(object actor,mixed * targets,string arg)
{
    if (!query_ability_prep_time())
    {
        prepare_ability(actor, targets, arg);
        return;
    }

    float speed, time;

    speed = max(2.0, actor->query_speed(5.0));
    time  = itof(query_ability_prep_time()) / 2.0;
    
    if (query_ability_hasted())
        time = time * speed / 5.0;
        
    time += (rnd() * time) + (rnd() * time);
    
    // Reset the two_handed_combat counter when the ability is scheduled
    two_handed_combat[actor] = 0.0;
    /* Making the ability time scale based on two-handed combat, as
     * seen in the function cb_calc_attackuse.
     */
    if (query_ability_dual_wield() && sizeof(actor->query_weapon(-1)) > 1)
    {
        float   old_time = time;
        int     extra = actor->query_skill(SS_2H_COMBAT);
        extra = extra > 20 ? extra / 2 : extra - 20;
        time = time * 100.0 / (100.0 + itof(extra));
        send_debug_message("timed_ability_2H", "Old time: " + ftoa(old_time)
        + " New time: " + ftoa(time));
        /* We need to keep track of the boost, so as not to be able to
         * abuse it by wielding a two handed weapon mid swing.
         */ 
        two_handed_combat[actor] = old_time - time;
    }
    
    if (IN_ARRAY(actor, m_indices(prepare_alarms)))
    {
        remove_alarm(prepare_alarms[actor]);
    }
    
    set_ability_pending(actor, environment(actor), 1); // backwards compatibility    
    prepare_alarms[actor] = set_alarm(time, 0.0, 
                                      &prepare_ability(actor,targets,arg));
    send_debug_message("timed_ability", "Ability preparing for "
                     + ftoa(time) + " seconds.");
    
    notify_prep_time(time, actor, targets);
}

public void
default_config_ability()
{
    ::default_config_ability();
    set_ability_hasted(1);
    set_ability_time(15);
}

/*
 * Function:    stop_ability
 * Description: At any time during the preparation or cooldown period,
 *              one can call this to remove the alarms.
 * Arguments:   player - player for which to stop the ability and remove
 *                       the alarms.
 * Returns:     0/1 - failure/success of stopping.
 */
public int
stop_ability(object player)
{
    int ability_stopped = 0;
    
    if (objectp(player))
    {
        if (IN_ARRAY(player, m_indices(prepare_alarms))
            && get_alarm(prepare_alarms[player]))
        {
            remove_alarm(prepare_alarms[player]);
            m_delkey(prepare_alarms, player);
            ability_stopped = 1;
        }
        
        if (IN_ARRAY(player, m_indices(cooldown_alarms))
            && get_alarm(cooldown_alarms[player]))
        {
            remove_alarm(cooldown_alarms[player]);
            m_delkey(cooldown_alarms, player);
            ability_stopped = 1;
        }
        
        if (ability_stopped)
        {
            /* remove the callback hooks */
            remove_ability_hooks(player);
            
            set_ability_pending(player, 0, 0); // backwards compat
            hook_stopped_ability(this_object(), player);
            return 1;
        }
    }
    return 0;
}

/*
 * Function:    query_ability_preparing
 * Description: This checks whether the ability is currently in the
 *              preparation mode. It checks the alarm to see if it
 *              is still running.
 * Arguments:   player - player to check the ability on
 * Returns:     0/1 - is not preparing/is preparing
 */
public int
query_ability_preparing(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (!IN_ARRAY(player, m_indices(prepare_alarms)))
    {
        return 0;
    }
    
    if (get_alarm(prepare_alarms[player]))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    query_ability_in_cooldown
 * Description: This checks whether the ability is currently in the
 *              cooldown mode. It checks the alarm to see if it
 *              is still running.
 * Arguments:   player - player to check the ability on
 * Returns:     0/1 - is not cooling down/is cooling down
 */
public int
query_ability_in_cooldown(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    if (!IN_ARRAY(player, m_indices(cooldown_alarms)))
    {
        return 0;
    }
    
    if (get_alarm(cooldown_alarms[player]))
    {
        return 1;
    }
    
    return 0;    
}

/*
 * Function:    query_ability_active
 * Description: This checks whether the ability is currently either in
 *              preparation or cooldown. It checks the alarm to see if it
 *              is still running.
 * Arguments:   player - player to check the ability on
 * Returns:     0/1 - is not active/is active
 */
public int
query_ability_active(object player)
{
    return (query_ability_preparing(player)
            || query_ability_in_cooldown(player));
}

/*
 * Function:    query_ability_remaining_time
 * Description: This method looks at the current alarms that are active
 *              on the ability and returns the results of the prepare
 *              and cooldown alarms. Adding the debugger tag for
 *              timed_ability also allows one to see the message.
 * Arguments:   player - the person executing the ability
 * Returns:     array of two floats: prepare and cooldown times remaining
 */
public mixed
query_ability_remaining_time(object player)
{
    mixed callValues;
    float prepare_time_remaining = 0.0;
    float cooldown_time_remaining = 0.0;
    
    if (!objectp(player)
        || !query_ability_active(player))
    {
        send_debug_message("timed_ability", "This ability is not active.");
        return ({ 0.0, 0.0 });
    }

    // Get the remaining time for prepare
    if (IN_ARRAY(player, m_indices(prepare_alarms))
        && pointerp(callValues = get_alarm(prepare_alarms[player])))
    {
        prepare_time_remaining = callValues[2];
    }
    
    if (IN_ARRAY(player, m_indices(cooldown_alarms))
        && pointerp(callValues = get_alarm(cooldown_alarms[player])))
    {
        cooldown_time_remaining = callValues[2];
    }

    if (prepare_time_remaining != 0.0)
    {        
        send_debug_message("timed_ability", "Prepare time remaining: "
                         + ftoa(prepare_time_remaining));
    }
    else if (cooldown_time_remaining != 0.0)
    {
        send_debug_message("timed_ability", "Cooldown time remaining: "
                         + ftoa(cooldown_time_remaining));
    }
                         
    return ({ prepare_time_remaining, cooldown_time_remaining });
}

/*
 * Function:    do_ability
 * Description: This is the call made by the command soul to execute the
 *              ability. For this class, we simply check to see if the
 *              ability is already running. If so, we will not allow it
 *              to continue. Otherwise, we pass it along to the base
 *              ability method.
 * Arguments:   arg - the string argument passed in by the player
 * Returns:     Always returns 1
 */
public int do_ability(string arg)
{
    object player = this_player();
    object * targets = ({});
    
    if (query_ability_preparing(player))
    {
        hook_already_active(this_object());
        return 1;
    }
    else if (query_ability_in_cooldown(player))
    {
        hook_special_in_cooldown();
        return 1;
    }

    return ::do_ability(arg);
}

/*
 * Function:    check_ability_pending (deprecated)
 * Description: This is a function for backwards compatibility only. This
 *              function was originally a part of ability.c and used to
 *              check using a property. However, with the change to check
 *              pending alarms, this is no longer necessary. Do not use
 *              this function unless you absolutely need to.
 * Arguments:   actor - person executing the ability
 *              room  - the room the person is in right now
 * Returns:     0 - ability is not pending and can be executed again
 *              1 - ability is currently pending and cannot be executed
 */
public int 
check_ability_pending(object actor, object room)
{
    if (!objectp(actor))
    {
        return 0;
    }
    
    if (query_ability_active(actor))
    {
        hook_already_active(this_object());
        return 1;
    }
        
    if (!validate_ability_stationary(actor, room))
    {
        hook_changed_env();
        return 1;
    }
    
    return 0;
}

/*
 * Function:    set_ability_pending (deprecated)
 * Description: This is a function for backwards compatibility only. This
 *              function was originally a part of ability.c and used to
 *              check using a property. However, with the change to check
 *              pending alarms, this is no longer necessary. Do not use
 *              this function unless you absolutely need to.
 * Arguments:   actor - person executing the ability
 *              room  - the room the person is in right now
 *              set   - whether to set it (1) or unset it (0)
 * Returns:     0 - ability is not pending and can be executed again
 *              1 - ability is currently pending and cannot be executed
 */
public void 
set_ability_pending(object actor, object room, int set)
{
    if (!objectp(actor))
    {
        return;
    }
    
    if (set)
    {
        actor->add_prop(LIVE_O_ACTION+Ability_name, this_object());
        set_ability_startloc(actor, room);
    }
    else
    {
        actor->remove_prop(LIVE_O_ACTION+Ability_name);
    }        
}

/*
 * Function:    display_hook_messages
 * Description: This is a debug function to be used on an ability to
 *              verify the output that a player will see. It is useful
 *              for verifying whether the ability will appear ok for
 *              players.
 * Arguments:   player - player who will see the messages
 * Returns:     nothing
 */
public void
display_hook_messages(object player)
{
    object oldtp = this_player();
    set_this_player(player);
    
    write("When this special is complete, it displays:\n\t");
    hook_special_complete();
    write("\n");

    write("When this special is in cooldown, it displays:\n\t");
    hook_special_in_cooldown();
    write("\n");
    
    write("When this special is stopped, it displays:\n\t");
    hook_stopped_ability(this_object(), player);
    write("\n");
    
    write("When this special is already active, it displays:\n\t");
    hook_already_active(this_object());
    write("\n");
    
    write("When this special is executed in a changed environment, it displays:\n\t");
    hook_changed_env();
    write("\n");
    
    set_this_player(oldtp);
}
