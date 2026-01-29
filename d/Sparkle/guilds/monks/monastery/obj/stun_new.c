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

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(60);
    set_stun_tohit(100);
    set_stun_chance(100); 
}

/*
 * Function:    m_land_plexus
 * Description: Called by shadow_base_combat in m_do_plexus, it sets the
 *              amount of time that the stun should have an effect. We
 *              ignore the slow time, which had virtually no effect and
 *              was incorrectly implemented.
 */
public void 
m_land_plexus (object monk, object target, float fStunTime, float fSlowTime)
{
    float total_cycle_time = fStunTime * (1.0 + (100.0 / itof(query_stun_combat_aid(target))));
    set_stun_cycle_time(ftoi(total_cycle_time));
    set_effect_caster(monk);
    set_effect_target(target);
    move(target, 1);
    start();
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

public void
hook_stun_cooldown_in_effect(object player)
{
    object monk = query_effect_caster();
    monk->catch_msg("You drive your open hand into " + QTNAME(player)
        + "'s solar plexus, but the blow seems to have no effect.\n");
    player->catch_msg(QCTNAME(monk) + " drives " + monk->query_possessive()
        + " open hand into your solar plexus, but the blow seems to "
        + "have no effect.\n");
    player->tell_watcher(QCTNAME(monk) + " drives " + monk->query_possessive()
        + " open hand into " + QTNAME(player) + "'s solar plexus, but "
        + "the blow seems to have no effect.\n", monk, ({ monk, player }));
}

public void
hook_stun_ended(object player)
{
    player->catch_msg ("You feel your breath returning, although you are still a bit windy.\n");
    tell_room (environment (player), QCTNAME (player) + " seems to regain " 
        + player->query_possessive() + " breath.\n", player, player);
}

public void
hook_stun_begin(object attacker, object target)
{
    // We don't show any messages for when the stun begins because
    // it is already incorporated into the plexus.
}
