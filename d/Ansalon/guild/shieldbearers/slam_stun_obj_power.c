/*
 * Stun Effect Object for the Shield Slam
 * 
 * This is the stun effect object for slam that handles stun in 
 * conjunction with the stun shadow. stun objects stack with one another.
 *
 * Created by Petros, September 2008
 *
 * Modifications:
 *  - Changing from tell_room to tell_watcher to reduce spam when testing.
 *    Petros, May 2009
 *  - ADded message for slammer when they don't have see fights on
 *    Petros, November 2009
 */
 
#pragma strict_types

#include "guild.h"

inherit "/d/Genesis/specials/std/stun_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes

// Global Variables

int hurt_level = 0;

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_power_slam_stun_object_");
    add_name( ({"power_slam_stun_obj" }) );
    set_short("hidden power slam stun object");    
    set_long("A power slam stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(100);
    set_stun_tohit(75);
    set_stun_chance(100); 
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(34);    
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 * Returns      : nothing
 */
public void
attack_blocked(object player)
{
    object enemy, attacker, defender;
    
    enemy = player->query_attack();
    attacker = query_effect_caster();
    defender = query_effect_target();
    if (enemy)
    {
        if (attacker == defender)
        {
            // This means that we stunned ourselves during the power
            // slam.
            player->catch_msg("You curse trying to recover from the "
                            + "effect of your powerful slam.\n");
            enemy->catch_msg(QCTNAME(player) + " curses trying to recover "
                           + "from the effect of the slam.\n");
            player->tell_watcher(QCTNAME(player) + " curses "
                    + "trying to recover from the effects of the slam.\n",
                      enemy, ({ player, enemy }));
         }
         else
         {
            if (hurt_level > 36)
            {
                // In this case, the person is collapsed on the
                // ground. Say that he is struggling instead
                player->catch_msg("You struggle from the ground to recover "
                                + "from being slammed.\n");
                enemy->catch_msg(QCTNAME(player) + " struggles from the "
                    + "ground to recover from being slammed.\n");
                player->tell_watcher(QCTNAME(player) + " struggles "
                    + "from the ground to recover from being slammed.\n",
                      enemy, ({ player, enemy }));                     
            }
            else
            {
                // There's a person that is being fought. We display messages
                // about the stun.
                player->catch_msg("You attempt to attack " + QTNAME(enemy)
                                 + ", but you are still stunned from being "
                                 + "slammed by a shield.\n");
                enemy->catch_msg(QCTNAME(player) + " makes an aggressive move "
                               + "towards you, but still seems out of breath "
                               + "from being slammed.\n");
                player->tell_watcher(QCTNAME(player) + " tries to "
                        + "attack " + QTNAME(enemy) + ", but seems to be "
                        + "having trouble catching " + player->query_possessive()
                        + " breath.\n", enemy, ({ player, enemy }));                     
            }
         }
    }        
}

public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You shrug off the attempts to hinder your "
                    + "movements.\n");
    player->tell_watcher(QCTNAME(player) + " shrugs off the attempt "
                       + "to hinder " + player->query_possessive()
                       + " movements.\n", ({ }));
}

public void
hook_stun_ended(object player)
{
    object attacker, defender;
    
    attacker = query_effect_caster();
    defender = query_effect_target();
    
    if (attacker == defender)
    {
        player->catch_msg("You shake off the effects of pounding your "
           + "enemy so hard.\n");
        player->tell_watcher(QCTNAME(player) + " seems to have " +
            "recovered from " +HIS(player)+ " daze.\n");
    }
    else
    {
        defender->catch_msg("You feel you have recovered from " +
            "the slam attack.\n");
        // We let the person slamming know his target has recovered
        attacker->catch_msg(QCTNAME(player) + " seems to have "
            + "recovered from the slam attack.\n");
        player->tell_watcher(QCTNAME(player) + " seems to have " +
            "recovered from the slam attack.\n", ({ attacker, defender }));
    }        
}

public void
hook_stun_begin(object attacker, object target)
{
    // We don't show any messages for when the stun begins because
    // it is already incorporated into the slam attack.
}

public void
set_phurt_value(int phurt)
{
    hurt_level = phurt;
}
