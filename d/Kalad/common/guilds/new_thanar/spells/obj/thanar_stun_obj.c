/*
 * /d/Kalad/common/guilds/new_thanar/spells/obj/thanar_stun_obj.c
 * Stun spell used by the Thanars in Kalad.
 * 
 * Created by Zignur, Jan 2018.
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
    set_name("thanar_spell_stun_object");
    add_name( ({"spell_stun_object" }) );
    set_short("hidden spell stun object");    
    set_long("A spell stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(45);
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
                         + ", but you are too terrified to do so.\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but "
                           + "seems frozen in terror.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but seems frozen "
                + "in terror.\n", ({ player, enemy }), player);
    } 
}

public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You feel the terror starting to fade away from you.\n");
    player->tell_watcher(QCTNAME(player) + " looks less terrified.\n", ({ }));
}

public void
hook_stun_ended(object player)
{
    player->catch_msg("You feel you managed to shake off the terror " +
        "that was holding you.\n");
    player->tell_watcher(QCTNAME(player) + " seems to have " +
        "recovered from the recent terrors.\n", ({ }));
}

public void
hook_stun_begin(object attacker, object target)
{
    target->catch_msg("The terrifying visage of Thanar fills you with "
        + "with unspeakable terrors, making you unable to move.\n");
    target->tell_watcher(QCTNAME(target) + " seems to terrified to "
        + "move.\n", ({ }) );
}
