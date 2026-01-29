/*
 * Stun Effect Object for the Templar TSap
 * 
 */
#pragma strict_types

#include "../local.h"

inherit "/d/Genesis/specials/std/stun_obj_base";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"


/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_templar_tsap_stun_object_");
    add_name( ({"templar_tsap_stun_obj" }) );
    set_short("hidden tsap stun object");    
    set_long("A tsap stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(5); // base combat aid
    set_stun_chance(50); // percentage chance of stunning
    set_stun_tohit(75); // hit percentage of the tsap
    set_stun_cycle_time(125);
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
                         + ", but you are still too dizzy.\n");
        enemy->catch_msg(QCTNAME(player) + " launches at you, but " +
                         "seems too disorientated to be any threat.\n");
        
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but seems to be "
                  + "having trouble orientating " + HIM(player)+"self.\n",
               ({ player, enemy }), player);
    }        
}

public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You try to regain your focus.\n");
    player->tell_watcher(QCTNAME(player) + " seems to be concentrating "+
                         "on regaining "+HIS(player)+" focus.\n");
}

public void
hook_stun_ended(object player)
{
    player->catch_msg("You no longer feel as dizzy.\n");
    player->tell_watcher(QCTNAME(player) + " seems less dizzy.\n");
}

public void
hook_stun_begin(object attacker, object target)
{
    attacker->catch_msg(QCTNAME(target) + " looks stunned!\n");
    target->catch_tell("You feel stunned!\n");
    attacker->tell_watcher(QCTNAME(target) + " looks stunned!\n", target);
}
