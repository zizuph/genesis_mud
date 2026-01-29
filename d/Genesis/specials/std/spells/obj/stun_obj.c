/*
 * Stun Effect Object for the Genesis Magic System Stun Spell
 * 
 * This is the stun effect object for the stun spell in the Genesis
 * Magic System. 
 *
 * Created by Petros, March 2010
 *
 */
 
#pragma strict_types

#include <macros.h>

inherit "/d/Genesis/specials/std/stun_obj_base";

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_spell_stun_object");
    add_name( ({"spell_stun_object" }) );
    set_short("hidden spell stun object");    
    set_long("A spell stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(100);
    set_stun_tohit(100);
    set_stun_chance(100); 
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(60);    
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
    object enemy;
    
    enemy = player->query_attack();
    if (enemy)
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You attempt to attack " + QTNAME(enemy)
                         + ", but find that you are stunned.\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but "
                           + "cannot seem to move.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but cannot seem to "
                + "move.\n", ({ player, enemy }), player);
    } 
}

public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You sense a tingling sensation as you successfully "
        + "ward off the magic trying to hinder your movement.\n");
    player->tell_watcher(QCTNAME(player) + " pauses briefly and seems to "
                       + "shrug off a magical attempt to hinder " 
                       + player->query_possessive() + " movements.\n", ({ }));
}

public void
hook_stun_ended(object player)
{
    player->catch_msg("You feel you have recovered from " +
        "the magical stunning attack.\n");
    player->tell_watcher(QCTNAME(player) + " seems to have " +
        "recovered from the magical stunning attack.\n", ({ }));
}

public void
hook_stun_begin(object attacker, object target)
{
    target->catch_msg("You feel the magic take hold of your limbs and "
        + "hold them in place, restricting your movement greatly.\n");
    target->tell_watcher(QCTNAME(target) + " seems to be under the control "
        + "of a spell, restricting " + target->query_possessive()
        + " movement.\n", ({ }) );
}
