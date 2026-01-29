/*
 * Stun Effect Object for the Genesis Magic System Stun Spell
 * 
 * This is the stun effect object for the stun spell in the Genesis
 * Magic System. 
 *
 * Created by Petros, March 2010
 *
 * Commented out set_stun_tohit seeing it duplicates chance to hit
 * with set_stun_chance, Arman August 2021
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit STUN_OBJ_BASE;

object  caster;
int     active;

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{   
    set_name("_dominate_stun_object");
    add_name("dominate_stun_object");
    set_short("hidden dominate spell stun object");    
    set_long("A dominate spell stun object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    set_stun_combat_aid(50);
    // set_stun_tohit(90);
    set_stun_chance(90); 
    set_stun_stats( TS_WIS );
    set_stun_skills( SS_FORM_ABJURATION );
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(60);    
}

public int
query_sohm_active()
{
    return active;
}

public string
query_sohm_dominate() 
{
    return caster->query_real_name();
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
    object enemy = player->query_attack();

    if (enemy)
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("Your mind is being dominated by " +QTNAME(caster)+
              ". You are unable to attack " + QTNAME(enemy)+ ".\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but "+
              HIS(player)+ " mind is dominated and " +HE(player)+
              " cannot seem to move.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but " +HIS(player)+
                " mind is dominated and " +HE(player)+ " cannot seem to "
                + "move.\n", ({ player, enemy }), player);
    } 
}

public void
hook_stun_cooldown_in_effect(object player)
{
    caster = query_effect_caster();

    player->catch_msg("Your mental barriers hold strong as you force "
        + "back an attempt by " +QTNAME(caster)+ " to dominate your mind.\n");
    caster->catch_msg(QCTPNAME(player) + " mental barriers hold strong "
                       + "as "+ HE(player)+ " forces back an attempt by you"+
                       " to dominate " +HIS(player)+ " mind.\n");
    player->tell_watcher(QCTPNAME(player) + " mental barriers hold strong "
                       + "as "+ HE(player)+ " forces back an attempt by " +
                       QTNAME(caster)+
                       " to dominate " +HIS(player)+ " mind.\n", ({ caster }));
}

public void
hook_stun_ended(object player)
{

    if(player->query_ghost())
        return;

    active = 0;
    player->catch_msg("You wrestle back control of your mind.\n");
    player->tell_watcher(QCTNAME(player) + " wrestles back control " +
            "of " +HIS(player)+ " mind.\n", ({ }));
}

public void
hook_stun_begin(object attacker, object target)
{

    caster = attacker;
    active = 1;
    
    target->catch_msg("You feel your mind being dominated by "
        +QTNAME(attacker)+
        ", your limbs no longer responding to your commands.\n");
    attacker->catch_msg(QCTNAME(target) + " is dominated by your controlling " +
        "enchantment, restricting " +target->query_possessive()+ " movement.\n"); 
    target->tell_watcher(QCTNAME(target) + " seems to be under the mental " +
        "control of "+QTNAME(attacker)+ ", who is restricting " +HIS(target)
        + " movement.\n", ({ attacker }) );
}
