/*
 * Stun Effect Object for the Vampire Mesmerize
 * 
 * This is the stun effect object for mesmerize to be used in
 * conjunction with the stun shadow. stun objects stack with one another.
 * Mesmerize makes both the vampire and the target stunned.
 *
 * Created by Petros, February 2009
 *
 * Modifications:
 *  - May 2009: Added is_mesmerize_object function for filtering
 */
 
#pragma strict_types

#include "../../guild.h"

inherit "/d/Genesis/specials/std/stun_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global variables
static object           defender = 0;

public void
set_defender(object player)
{
    defender = player;
}

public object
query_defender()
{
    return defender;
}

public int
is_mesmerize_object()
{
    return 1;
}

public void
create_effect()
{
    set_name("_mesmerize_obj");
    add_name( ({"mesmerize_stun_obj" }) );
    set_short("hidden mesmerize stun object");    
    set_long("A vampire mesmerize stun object. One should not be able to "
        + "see it in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(100);
    set_stun_tohit(100);
    set_stun_chance(100); 

    // This gives 10 seconds of stun, and 10 seconds of cooldown
    set_stun_cycle_time(20);        
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
    object enemy, attacker, target;
    
    enemy = player->query_attack();
    attacker = query_effect_caster();
    target = query_effect_target();
    if (enemy)
    {
        if (attacker == target)
        {
            // This means that we stunned ourselves during the mesmerize
            player->catch_msg("You maintain your mental hold over "
                + QTNAME(defender) + " and are unable to focus on "
                + "anything else.\n");
            enemy->catch_msg(QCTNAME(player) + " seems to be deep in "
                + "thought and does not make any aggressive actions "
                + "towards you.\n");
            player->tell_watcher(QCTNAME(player) + " seems "
                    + "to be deep in thought and does not make any "
                    + "aggressive actions towards " + QTNAME(enemy),
                    enemy, ({ player, enemy }));
         }
         else
         {
            // This is for the person who has been mesmerized by the
            // vampire.
            player->catch_msg("You attempt to attack " + QTNAME(enemy)
                + ", but you find yourself unable to do so as you struggle "
                + "with your inner demons.\n");
            enemy->catch_msg(QCTNAME(player) + " seems to be struggling "
                + "internally and unable to make an aggressive action "
                + "towards you.\n");
            player->tell_watcher(QCTNAME(player) + " seems "
                + "to be struggling internally and unable to make "
                + "an aggressive action towards " + QTNAME(enemy) + ".\n", 
                enemy, ({ player, enemy }));                     
         }
    }        
}

public void
hook_stun_cooldown_in_effect(object player)
{
    object caster;
    
    caster = query_effect_caster();
    if (player == defender)
    {
        player->catch_msg("You sense an invading presence try to hinder "
            + "your movements, but you easily shrug off the attempts.\n");
        caster->catch_msg("Your attempt to invade the mind of "
            + QTNAME(player) + " is met with strong resistance.\n");
    }
}

public void
hook_stun_ended(object player)
{
    object attacker, target;
    
    attacker = query_effect_caster();
    target = query_effect_target();
    
    if (target == defender)
    {
        attacker->catch_msg("Your feel " + QTNAME(defender) 
            + " push you back out of " + POSS(defender)
            + " mind.\n");
        target->catch_msg("The mental attack subsides, leaving your "
            + "mind completely under your control once again.\n");
    }
    
    // No messages for stun object on caster.
}

public void
hook_stun_begin(object attacker, object target)
{
    if (target == defender)
    {
        target->catch_msg("You feel an alien presence in your mind, "
            + "reaching deep within you to play upon your most animal "
            + "instincts. Fear, rage, confusion, each pulls itself to "
            + "the forefront of your mind, leaving you completely unable "
            + "to focus on anything but battling your own inner demons.\n");
        attacker->catch_msg("You press yourself into " + QTNAME(target)
            + "'s mind, playing upon " + POSS(target) + " hopes, fears "
            + "and primal emotions in an attempt to distract " + POSS(target)
            + " from the battle at hand.\n");    
    }
    
    // No messages for the stun object on the caster himself.
}
