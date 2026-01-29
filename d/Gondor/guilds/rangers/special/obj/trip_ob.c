/*
 * Stun Effect Object Dragon Order Plexus
 * 
 * This is the stun effect object plexus. It uses the standard stun effect
 * object as a base and merely adds customized messages.
 *
 * Created by Petros, December 2010
 */
 
#pragma strict_types

#include "/d/Genesis/specials/local.h"    
inherit STUN_OBJ_BASE;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

int in_cooldown = 0;

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_ranger_trip_obj");
    add_name( ({"ranger_trip_obj" }) );
    set_short("hidden ranger trip object");    
    set_long("A ranger trip stun object. One should not be able to see it "
           + "in their inventory.\n");
           
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
    if (objectp(enemy))
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You attempt to attack " + QTNAME(enemy)
            + ", but you struggle to get on your feet.\n");
        enemy->catch_msg(QCTNAME(player) + " makes an aggressive move "
            + "towards you, but is struggling to get on "
            + player->query_possessive() + " feet.\n");
        player->query_combat_object()->
            tell_watcher(QCTNAME(player) + " tries to "
            + "attack " + QTNAME(enemy) + ", but seems to be "
            + "having trouble getting on " + player->query_possessive() 
            + " feet.\n" , ({ player, enemy }));                     
    }
}

public void
hook_stun_cooldown_in_effect(object player)
{
}

public void
hook_stun_ended(object player)
{
    in_cooldown = 1;
    player->catch_tell("You recover your balance again.\n");
    tell_room(environment(player), "You notice that " +
        QTNAME(player) + " has recovered " +
        player->query_possessive() + " balance again.\n", player);
                    
    if (query_effect_caster() && environment(player) == environment(query_effect_caster())
        && query_effect_caster()->check_seen(player))
    {
        query_effect_caster()->catch_msg(QCTNAME(player) +
                " glares angrily at you.\n");
        player->catch_msg("You glare angrily at " +
                QTNAME(query_effect_caster()) + ".\n");
        tell_room(environment(player), QCTNAME(player) + 
            " glares angrily at " + QTNAME(query_effect_caster()) + ".\n", 
            ({ player, query_effect_caster() }));
    }
}

public void
hook_stun_failed(object attacker, object target)
{
    if (!objectp(target))
    {
        return;
    }
    
    if (objectp(attacker))
    {   
        if (in_cooldown)
        {
            attacker->catch_msg(QCTNAME(target) + 
               " is still too focused on you from your last trip.\n");
        }
        else
        {
            attacker->catch_msg("You try to trip " + QTNAME(target) + 
               ", but they are already flailing from your trip.\n");
        }
    }
}

public void
hook_stun_begin(object actor, object target)
{    
    actor->catch_msg("You manage to trip " + QTNAME(target) +
            " without difficulty. " + capitalize(target->query_pronoun()) +
            " stumbles around, wavering while trying to regain balance.\n");
    target->catch_msg(QCTNAME(actor) +
            " skillfully trips you, and you " + 
            "stumble around, waving your arms, trying to regain balance.\n");

    actor->query_combat_object()->
        tell_watcher(QCTNAME(actor) + " manages to trip " +
        QTNAME(target) + " without difficulty, and " + QTNAME(target) + " " +
        "stumbles around, wavering while trying to regain balance.\n", 
        target, actor);
}
