/*
 * Stun Effect Object Dragon Order Plexus
 * 
 * This is the stun effect object plexus. It uses the standard stun effect
 * object as a base and merely adds customized messages.
 *
 * Created by Petros, December 2010
 */
 
#pragma strict_types
    
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
private static string *asStunMessages = ({
  "the blow to your abdomen rendered you unable to do that.",
  "sharp pain in your abdomen prevents you doing that.",
  "you feel like throwing up rather than doing that.",
  "your limbs refuse to follow your orders." });

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_plexus_stun_obj");
    add_name( ({"plexus_stun_obj" }) );
    set_short("hidden plexus stun object");    
    set_long("A plexus stun object. One should not be able to see it "
           + "in their inventory.\n");
    // 25% combat aid == 20% stun
    set_stun_combat_aid(100);
    // By default stun always hits 100%, we set the stun chance parameter
    // in plexus.c
    // set_stun_chance(100);

    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(45);

    setuid();
    seteuid(getuid());
}


/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                prevented because the player is stunned
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
    if (defender->query_prop(LIVE_I_UNDEAD) == 0)
    {
        if (objectp(enemy))
        {
            // There's a person that is being fought. We display messages
            // about the stun.
            player->catch_msg("You attempt to attack " + QTNAME(enemy)
                             + ", but " + one_of_list (asStunMessages) + "\n");
            enemy->catch_msg(QCTNAME(player) + " makes an aggressive move "
                           + "towards you, but still seems to be out of "
                           + "breath.\n");
            player->tell_watcher(QCTNAME(player) + " tries to "
                    + "attack " + QTNAME(enemy) + ", but seems to be "
                    + "having trouble catching " + player->query_possessive()
                    + " breath.\n", enemy, ({ player, enemy }));                     
        }
    }
    else
    {
        if (objectp(enemy))
        {
            // There's a person that is being fought. We display messages
            // about the stun.
            player->catch_msg("You attempt to attack " + QTNAME(enemy)
                             + ", but " + one_of_list (asStunMessages) + "\n");
            enemy->catch_msg(QCTNAME(player) + " makes an aggressive move "
                           + "towards you, but still seems to be suffering "
                           + "impaired movement.\n");
            player->tell_watcher(QCTNAME(player) + " tries to "
                    + "attack " + QTNAME(enemy) + ", but seems to be "
                    + "having " + player->query_possessive()
                    + " movement impaired.\n", enemy, ({ player, enemy }));                     
        }
    }
}

public void
hook_stun_cooldown_in_effect(object player)
{
    object monk = query_effect_caster();
    object defender = query_effect_target();

    if (defender->query_humanoid())
    {
        monk->catch_msg("You drive your open hand into " + QTPNAME(player)
            + " solar plexus, but the blow seems to have no effect.\n");
        player->catch_msg(QCTNAME(monk) + " drives " + monk->query_possessive()
            + " open hand into your solar plexus, but the blow seems to "
            + "have no effect.\n");
        player->tell_watcher(QCTNAME(monk) + " drives " + monk->query_possessive()
            + " open hand into " + QTPNAME(player) + " solar plexus, but "
            + "the blow seems to have no effect.\n", monk, ({ monk, player }));
    }
    else
    {
        monk->catch_msg("You drive your open hand into " + QTPNAME(player)
            + " body, but the blow seems to have no effect.\n");
        player->catch_msg(QCTNAME(monk) + " drives " + monk->query_possessive()
            + " open hand into your body, but the blow seems to "
            + "have no effect.\n");
        player->tell_watcher(QCTNAME(monk) + " drives " + monk->query_possessive()
            + " open hand into " + QTPNAME(player) + " body, but "
            + "the blow seems to have no effect.\n", monk, ({ monk, player }));
    }
}

public void
hook_stun_ended(object player)
{
    if (player->query_prop(LIVE_I_UNDEAD) == 0)
    {
        player->catch_msg ("You feel your breath returning, although you are still a bit windy.\n");
        tell_room (environment (player), QCTNAME (player) + " seems to regain " 
            + player->query_possessive() + " breath.\n", player, player);
    }
    else
    {
        player->catch_msg ("You feel your movement returning, although you are still a bit shaken.\n");
        tell_room (environment (player), QCTNAME (player) + " seems to regain " 
            + player->query_possessive() + " movement.\n", player, player);     
    }
}

public void
hook_stun_begin(object oActor, object oTarget)
{
    if (oTarget->query_humanoid())
    {
        oActor->catch_msg("You strike " + QTPNAME(oTarget) +
            " solar plexus with your " +
            "open hand, stunning " + oTarget->query_objective() + ".\n");
        oTarget->catch_msg(QCTNAME(oActor) +
            " strikes your solar plexus with " + oActor->query_possessive() +
            " open hand. You feel numb.\n");
        oTarget->tell_watcher(QCTNAME(oActor) + " drives " +
            oActor->query_possessive() + " open hand into " +
            QTPNAME(oTarget) + " solar plexus, stunning " +
            oTarget->query_objective() + ".\n",
            oActor);
    }
    else
    {
        oActor->catch_msg("You strike " + QTPNAME(oTarget) +
            " body with your " +
            "open hand, stunning " + oTarget->query_objective() + ".\n");
        oTarget->catch_msg(QCTNAME(oActor) +
            " strikes your body with " + oActor->query_possessive() +
            " open hand. You feel numb.\n");
        oTarget->tell_watcher(QCTNAME(oActor) + " drives " +
            oActor->query_possessive() + " open hand into " +
            QTPNAME(oTarget) + " body, stunning " +
            oTarget->query_objective() + ".\n",
            oActor);   
    }
}
