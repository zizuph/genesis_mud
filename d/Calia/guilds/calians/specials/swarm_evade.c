/*
 * Swarm Evade Object
 * 
 * Calians have the ability to evade during a swarming attack.
 * This object will determine the strength
 * of the evade depending on the number of
 * Calians who are attacking the same enemy.
 *
 * Created by Petros, June 2008
 *
 * Modification Log
 *   9/4/2008
 *   - Added check for FILTER_PRESENT so that it doesn't result in 
 *     runtime error. (Petros)
 */
 
#pragma strict_types

#include "defs.h"

inherit EVADE_BASE_OBJ;
inherit SPECIALS_UTILITY;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

#include DEBUGGER_TELL
#include CALIAN_HEADER

/*
 * Function     : is_swarm_evade
 * Description  : Easy way to identify a swarm evade object
 * Arguments    : none
 * Returns      : 1 - always returns true
 */
public int
is_swarm_evade()
{
    return 1;
}

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_swarm_evade_object_");
    add_name( ({"swarm_evade_object" }) );
    set_short("hidden calian swarm evade object");    
    set_long("The object that grants swarming evade to a Calian. This "
           + "should not be visible by players.\n");

    setuid();
    seteuid(getuid());

    set_evade_stats( TS_WIS );
    set_evade_skills( SS_SWARM_KNOWLEDGE );
    // 25% combat aid == 20% evade
    set_evade_combat_aid(SWARM_EVADE_CAID);
}                           

/*
 * Function     : remove_swarm_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_swarm_object()
{
    remove_object();
}

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{ 
    // The swarm evade has the following conditions:
    // 1. The defender must be attacking the same enemy as the
    //    Calian receiving the evade benefit
    // 2. If a Calian is being attacked, it will use its own
    //    evade capability, and will not provide it for someone
    //    else
    object * team, * calians, * enemies;
    object defender;

    defender = query_effect_caster();
    if (!defender)
    {
        send_debug_message("swarm_evade", "Defender is no longer valid, "
                         + "maybe from quitting.");
        set_alarm(0.1, 0.0, &remove_swarm_object());
        return 0;
    }
    enemies = filter(all_inventory(environment(defender)), 
                     &is_attacking_this_living(,defender)); 
    
    if (defender != player
        && sizeof(enemies) > 0)
    {
        // If a Calian is being attacked, then it can't help other
        // Calians defend. it will use its evade capability for
        // itself.
        send_debug_message("swarm_evade", "The evade benefit does not "
                         + "apply to " 
                         + capitalize(player->query_real_name()) + ".");
        return 0;
    }
    
    if (SWARM_ABILITY->query_ability_active(player))
    {
        // If a Calian is either preparing a swarm, or is in swarm
        // cooldown, then the swarm evade cannot be active. This is to
        // prevent uber tanking when Calians are doing a rotating swarm.
        send_debug_message("swarm_evade", "The evade benefit does not "
            + "apply to " + capitalize(player->query_real_name())
            + " when swarm is active.");
        return 0;
    }
    
    if (defender->query_attack() != player->query_attack())
    {
        // If the defender is not attacking the same enemy as
        // the player, then the evade cannot be used
        send_debug_message("swarm_evade", "The defender and the "
                         + "tanker are not attacking the same "
                         + "enemy, thus the swarm evade does not "
                         + "occur.");
        return 0;
    }
    
    if (defender != player
        && player->query_attack()->query_attack() != player)
    {
        // This requirement that the person the tanker is attacking
        // must be attacking back was found to be necessary during
        // balance review. This prevents the swarm benefit from
        // going to more than one person at a time. (eg. when there
        // are two Calian tankers, both attacking the same enemy)
        send_debug_message("swarm_evade", "Calian tanker's enemy is "
                         + "focused elsewhere. Therefore, no swarm "
                         + "evade benefits.");
        return 0;
    }
    
    team = player->query_team_others();
    team -= ({ 0 });
    // We need to set this_player because FILTER_PRESENT_LIVE
    // depends on this_player()
    object oldtp = this_player();
    set_this_player(player);                         
    team = FILTER_PRESENT_LIVE(team);
    set_this_player(oldtp);
    calians = filter(team, &->has_calian_shadow());
    
    if (sizeof(calians) == 0)
    {
        send_debug_message("swarm_evade",
                           capitalize(player->query_real_name())
                         + " is not in a team with other Calians, so "
                         + "there are no evade benefits.");        
        return 0;
    }
    
    if (defender != player
        && !IN_ARRAY(defender, team))
    {
        send_debug_message("swarm_evade", 
                           capitalize(player->query_real_name())
                         + " is not in the same team as the defender "
                         + capitalize(defender->query_real_name()));
        return 0;
    }
    
    return 1;
}

/*
 * Function     : query_evade_strength
 * Description  : Function that will be used to gauge the strength of
 *                the evade based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the evasion percentage
 */
public int
query_evade_strength(object player, object attacker, int attack_id)
{
    int strength, skill_modifier, stat_modifier;
    float num_calians;
    object * team, * calians;

    strength = ::query_evade_strength(player, attacker, attack_id);
    if (query_effect_caster() != player)
    {
        // We cap the swarm evade percentage aid for all teammates to
        // 33% (50% combat aid). That means, no matter how many team
        // mates there are, the cap will always be 50% caid. The aid
        // starts at 10% evade up until 4 teammates.
        team = player->query_team_others();
        // Need to set this_player() because FILTER_PRESENT_LIVE
        // depends on this_player()
        object oldtp = this_player();
        set_this_player(player); 
        team = FILTER_PRESENT_LIVE(team);
        set_this_player(oldtp);
        calians = filter(team, &->has_calian_shadow());
        num_calians = itof(sizeof(calians));
        if (num_calians > 0.0)
        {
            strength = min(ftoi((1.0 - exp(log(0.67) / num_calians)) 
                           * 100.0) + 1, SWARM_EVADE_ASSIST_CAID);
            // Now we need to modify the strength by the stats & skills        
            skill_modifier = calc_base_skill(player, query_effect_skills());
            stat_modifier = calc_stat_modifier(player, query_effect_stats());        
            strength = strength * skill_modifier;
            strength = strength * F_STR_FACTOR(stat_modifier) / 10000;
            strength = strength * query_combat_aid_modifier(player) / 100;                               
        }
    }

    send_debug_message("swarm_evade", "Swarm evade strength: " + strength);
    return strength;
}   

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    object defender;
    object * exclude_list;
    string defender_desc, player_desc, attacker_desc, watcher_desc;
    
    defender = query_effect_caster();

    exclude_list = ({ player, attacker });
    if (player == defender)
    {
        defender_desc = "";
        // The evade comes from the player himself.
        switch (random(2))
        {
        case 1:
            player_desc = "Oblivious to your coordinated movements with "
                        + "your fellow Calians, " + QTNAME(attacker) 
                        + " strikes out at you and you easily move away "
                        + "from " + attacker->query_possessive() 
                        + " attack.";
            attacker_desc = "You strike out at " + QTNAME(player)
                          + ", but at the last moment you are distracted "
                          + "by the coordinated movements of " 
                          + player->query_possessive() + " team and "
                          + QTNAME(player) + " is able to dodge your "
                          + "attack.";
            watcher_desc = QCTNAME(attacker) + " strikes out at " 
                         + QTNAME(player) + ", but seems to be distracted "
                         + "by the coordinated movements of "
                         + player->query_possessive() + " team. At the "
                         + "last moment, " + QTNAME(player) + " is able "
                         + "to dodge " + attacker->query_possessive()
                         + " attack.";
            break;
            
        case 0:
        default:
            player_desc = "Utilizing wolf-like movements, "
                        + "you move to you left, then to your right, " 
                        + "causing " + QTNAME(attacker) + " to swing at "
                        + "nothing but empty air.";
            attacker_desc = "You swing at " + QTNAME(player) + " but you "
                        + "don't hit anything as " + QTNAME(player)
                        + " moves strangely around your attack.";
            watcher_desc = QCTNAME(attacker) + " swings at " 
                        + QTNAME(player) + " but " 
                        + attacker->query_possessive() + " attack lands "
                        + "on empty air as " + QTNAME(player) + " moves "
                        + "in a strange fashion.";
        }
    }
    else
    {
        exclude_list += ({ defender });
        // One of the teammates is providing the evade
        player_desc = "Unable to react quickly enough, you watch "
                    + "expectantly as " + QTNAME(attacker)
                    + " strikes at you, but at the last moment, "
                    + QTNAME(defender) + " turns "
                    + defender->query_possessive() + " weapon while "
                    + "swarming and deflects the blow for you.";
        attacker_desc = "You strike at " + QTNAME(player) + " but "
                    + "as you are about to make contact, your blow "
                    + "is deflected by " + QTNAME(defender) + "'s "
                    + "weapon.";
        watcher_desc = QCTNAME(attacker) + " strikes out at "
                    + QTNAME(player) + ", but as the blow is about to "
                    + "hit true, " + QTNAME(defender) + " moves "
                    + defender->query_possessive() + " weapon in to "
                    + "deflect the blow.";
        defender_desc = "You see " + QTNAME(player) + " about to "
                    + "receive a blow from " + QTNAME(attacker)
                    + " and quickly thrust your weapon to deflect "
                    + "the blow.";                    
    }
    
    player->catch_msg(player_desc + "\n");
    attacker->catch_msg(attacker_desc + "\n");
    special_tell_watcher(player, watcher_desc + "\n", attacker, exclude_list);
    if (strlen(defender_desc))
    {
        defender->catch_msg(defender_desc + "\n");
    }
}

