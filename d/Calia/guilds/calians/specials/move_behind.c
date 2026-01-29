/*
 * Implementation of the Calian Move Behind Special
 *
 * Created by Petros, May 2008
 * Modifications:
 *   - Sep 25, 2015 - Add check for Knight Charging (Mirandus)
 *
 */
#pragma strict_types

#include "defs.h"

inherit TIMED_ABILITY_LIB;
inherit SPECIALS_UTILITY;
inherit CALIAN_UTILITY;

#include CALIAN_HEADER
#include COUNCIL_HEADER
#include DEBUGGER_TELL

#include <ss_types.h>
#include <cmdparse.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <adverbs.h>
#include "/std/combat/combat.h"

// Prototypes
public void     do_move_behind(object player, object friend);
public void     on_already_move_behind_success(object player);
public object * target_friend(object actor, string str);

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_ability_time(1);
    set_ability_visual(0);    
    set_ability_name("move behind");
    set_ability_offensive(0);    

    set_ability_target(target_friend);
}

/* 
 * Function:      reattack_object 
 * Description:   Called to make an enemy re-attack someone whom 
 *                a Calian moved behind. 
 * Arguments:     object enemy   - the person attacking 
 *                object friend  - the person attacked 
 */ 
public void 
reattack_object(object enemy, object friend) 
{ 
    enemy->stop_fight(friend); 
    enemy->attack_object(friend); 
} 

/* 
 * Function:      stopattack_object 
 * Description:   Called to make an enemy stop fighting a Calian who 
 *                moves behind in a ROOM_M_NO_ATTACK room. 
 * Arguments:     object enemy   - the person attacking 
 *                object calian  - the person who moved behind 
 *                object friend  - person who is now in front 
 */ 
public void 
stopattack_object(object enemy, object calian, object friend) 
{ 
    enemy->stop_fight(calian); 
    calian->stop_fight(enemy); 
    if (friend->query_attack() == enemy) 
    { 
        enemy->stop_fight(friend); 
        enemy->attack_object(friend); 
    } 
} 


/* 
 * Function:      resolve_ability
 * Description:   Called to execute the ability after all the 
 *                checks have been done.
 * Arguments:     actor   - person executing the special
 *                items   - array of items from check_required_items
 *                targets - array of targets for this special
 *                resist  - the list of resistances
 *                result  - the list of results, one per target
 * Returns:       nothing
 */ 
static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    if (sizeof(targets))
    {
        do_move_behind(actor, targets[0]);
    }
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object friend, attacker;
    object * team, *enemies;
    int d, tm, number_enemies;
    
    // By this point, we know that the first object in targets is the friend
    friend = targets[0];
    
    // Check that target friend is around. 
    if (environment(player) != environment(friend))
    { 
        player->catch_tell("Move behind whom [how]?\n"); 
        return 0; 
    } 

    // Can't move behind a non-living. 
    if (!living(friend)) 
    { 
        player->catch_tell("You can only move behind living beings " 
                         + "if you actually expect to get away.\n"); 
        return 0; 
    } 

     // Check that the friend isn't attacking the Calian. 
     // This has happened in accidents! 
    if (friend->query_attack() == player) 
    { 
        player->catch_tell("You can't move behind someone who is "
                         + "attacking you!\n");
        return 0; 
    } 

 	// Check to see if the friend is a knight who is trying to charge
	// Shouldn't be able to move behind a charging Knight
    if (friend->has_knight_charge_shadow())
	{
		player->catch_tell("You can't move behind someone while they "
		                   + "are galloping away from battle!\n");
		return 0;
	}
    
    /* 
     * Check that player hasn't attacked someone within last 3 secs. 
     */ 
    if ((d = (tm = time()) - player->query_prop(CALIAN_I_LAST_ATTACK_TIME))
        < 3) 
    { 
        player->catch_tell("Having recently launched an attack you are "
                         + "not yet ready to move behind.\n"); 
        return 0; 
    } 

    /* 
     * Get team and attacked objects. 
     */ 
    team = player->query_team_others(); 
    attacker = player->query_attack(); 

    /* 
     * Check for carried livings like pigeons and such :) 
     */ 
    if (objectp(present(attacker, player))) 
    { 
        player->catch_tell("You can't get away from something you are " 
                         + "carrying!\n"); 
        return 0; 
    } 

    /* 
     * Find out the present enemies of the Calian. 
     */ 
    enemies = filter(all_inventory(environment(player)), 
                     &is_attacking_this_living(,player)); 
    number_enemies = sizeof(enemies); 

    /* 
     * Check whether attempt is possible. Criteria are: skill level, 
     * number of enemies, being in a team, presence of friend on team, 
     * whether ready to moved behind again. 
     */ 
    if (!player->query_skill(SS_MOVE_BEHIND)) 
    { 
        player->catch_tell("You have no skill in moving behind team "
                         + "members during battle!\n"); 
        return 0; 
    } 
    else if (!number_enemies) 
    {
        on_already_move_behind_success(player);
        return 0; 
    } 
    else if (!sizeof(team)) 
    { 
        player->catch_tell("You are not a member of a team.\n");
        return 0; 
    } 
    else if (member_array(friend, team) == -1) 
    { 
        player->catch_msg(QCTNAME(friend) + " is not a member of your "
                        + "team.\n");
        return 0; 
    }

    if (SWARM_ABILITY->query_ability_preparing(friend))
    {
        player->catch_msg(QCTNAME(friend) + " is in the middle of "
            + "an attempt to swarm! You should not interrupt the delicate "
            + "dance that your team is coordinating.\n");
        return 0;
    }
        
    return 1;
}

/*
 * Function name: query_move_behind_sucess
 * Description:   Gives the result of whether the move behind attempt is
 *                successful or not. It uses resolve_task to perform the
 *                opposed check.
 * Arguments:     player  - player trying to move behind
 *                friend  - the person the player is trying to move behind
 *                enemies - array of enemies attacking the player
 * Returns:       0/1 - failure/success
 */
public int
query_move_behind_success(object player, object friend, object * enemies)
{
    object attacker; // a random attacker from list of enemies
    int friend_modifier, enemy_modifier, mb_skill, last_time;
    
    // We will use resolve_task to determine success
    // Task:   move behind a friend when being attacked
    // Calian    : Dex, Wisdom, Int, Move Behind skill
    //             friend's str, friend's dis
    // Attackers : Dex, Wisdom, Number of Attackers * 20
    // We need to determine success.

    mb_skill = player->query_skill(SS_MOVE_BEHIND);
    // If a person cannot see, we modify their mb_skill by the
    // blindfighting skill
    if (!CAN_SEE_IN_ROOM(player))
    {
        int blind_skill = player->query_skill(SS_BLIND_COMBAT);
        mb_skill = max(min(5, mb_skill), mb_skill * blind_skill / 100);
    }
        
    attacker = enemies[random(sizeof(enemies))]; 
    enemy_modifier = sizeof(enemies) * 20;
    friend_modifier = (friend->query_stat(SS_STR) 
                       + friend->query_stat(SS_DIS)) / 2;
    last_time = time () - player->query_prop(CALIAN_I_LAST_MOVE_BEHIND);
    if (last_time < ftoi(player->query_speed(5)))
    {
        // The difficulty of moving behind is decreases as
        // time increases from the last move behind
        enemy_modifier += (ftoi(player->query_speed(5)) - last_time) * 20;
    }

    if (player->resolve_task(TASK_EASY, 
               ({ SS_MOVE_BEHIND,
                  SKILL_WEIGHT, mb_skill,
                  SKILL_AVG, TS_DEX, TS_WIS, TS_INT, SKILL_END,
                  SKILL_VALUE, friend_modifier }),
                  attacker,
                  ({ TS_DEX, TS_WIS, SKILL_VALUE, enemy_modifier })) >= 0)
    {
        // If we reached the task number of TASK_EASY, this is a
        // success.
        return 1;
    }            
    
    return 0;
}

/*
 * Function name: resolve_task_move_behind_test
 * Description:   This runs the resolve_task for people of stat 100
 *                against different number of enemies. Move Behind
 *                skill is maxed by default.
 * Arguments:     player       - player trying to move behind
 *                num_enemies  - number of enemies attacking player
 *                mbskill      - the move behind skill
 * Returns:       The percentage of success out of 10000 tries
 */
public varargs int
resolve_task_move_behind_test(object player, int num_enemies, int mbskill)
{
    // The default check of 2 enemies, and 100 mb skill yields a success
    // rate of approximately 90%.
    int num_success;
    
    if (!num_enemies)
    {
        // Default number of enemies
        num_enemies = 2;
    }
    
    if (!mbskill)
    {
        // Default skill to 100
        mbskill = 100;
    }
    num_success = 0;
    for (int i = 0; i < 10000; ++i)
    {
        if (player->resolve_task(TASK_EASY, 
            ({ SKILL_VALUE, mbskill,
               SKILL_VALUE, mbskill,    // dex, wis, int avg
               SKILL_VALUE, 100 }), // friend modifier
            player,
            ({ SKILL_VALUE, 100,    // dex
               SKILL_VALUE, 100,    // wis
               SKILL_VALUE, num_enemies * 20})) // enemy modifier
             >= 0)
        {
            ++num_success;
        }            
    }
    
    player->catch_tell("Success rate is: " 
                     + ftoa(itof(num_success) / itof(100)) + "\n");
}

/*
 * Function name: on_move_behind_success
 * Description  : A hook for executing extra code when there is a success
 *                for move behind.
 * Arguments    : none
 * Returns      : nothing
 */
public void
on_move_behind_success()
{
}

/*
 * Function name: on_already_move_behind_success
 * Description  : A hook for executing extra code when there is a success
 *                for move behind because they are not being attacked
 * Arguments    : player - player trying to move behind
 * Returns      : nothing
 */
public void
on_already_move_behind_success(object player)
{
    player->catch_tell("No-one is attacking you!\n");    
}

/*
 * Function name: on_move_behind_failure
 * Description  : A hook for executing extra code when there is a failure
 *                for move behind.
 * Arguments    : player - player executing the move behind
 * Returns      : nothing
 */
public void
on_move_behind_failure(object player)
{
}

/*
 * Function name: do_move_behind
 * Description  : Actual code that executes the move behind ability
 * Arguments    : player - player executing the move behind action
 *                friend - the friend being moved behind
 * Returns      : nothing
 */
public void
do_move_behind(object player, object friend)
{
    object * enemies;
    string current_adverb;
    
    object oldtp = this_player();
    set_this_player(player);
    // Get the list of people attacking this player
    enemies = filter(all_inventory(environment(player)), 
                     &is_attacking_this_living(,player)); 
    
    player->set_mb_target(friend->query_real_name());
    if (query_move_behind_success(player, friend, enemies))
    {
        current_adverb = player->query_mb_adverb();
        if (!stringp(current_adverb) || !strlen(current_adverb)) 
        {
            current_adverb = "quickly"; // default 
        }
        
        if (environment(player)->query_prop(ROOM_M_NO_ATTACK)) 
        { 
            map(enemies, &stopattack_object(,player, friend)); 
            player->catch_msg("You " + current_adverb
                            + " move behind " + QTNAME(friend) + ".\n");
            friend->catch_msg(QCTNAME(player) + " " + current_adverb
                            + " moves behind you.\n"); 
            tell_room(environment(player), QCTNAME(player) + 
                " " + current_adverb + " moves behind " + 
                QTNAME(friend) + ".\n", ({ player, friend }) ); 
            send_debug_message("mb_ra", player->query_real_name() 
                             + " successfully moves behind " 
                             + friend->query_real_name() + " in a "
                             + "no-attack room.");
        } 
        else 
        {
            player->add_prop(CALIAN_I_LAST_MOVE_BEHIND, time());
            map(enemies, &reattack_object(,friend)); 
            // If one moves behind someone, then that person has a lower
            // swarm potential. This is to prevent the rotating swarms
            // from having too much combat aid.
            friend->add_prop(CALIAN_MOVE_BEHIND_TARGET_TIME, time());
            
            player->catch_msg("You " + current_adverb + " move behind " 
                            + QTNAME(friend) + " and your enemies move "
                            + "to attack " + friend->query_objective()
                            + ".\n");
            friend->catch_msg(QCTNAME(player) + " " + current_adverb
                            + " moves behind you, and "
                            + player->query_possessive() + " enemies "
                            + "move to attack you!\n");                           
            tell_room(environment(player), QCTNAME(player) + " " 
                    + current_adverb + " moves behind " + QTNAME(friend) 
                    + ", who is attacked by " + player->query_possessive()
                    + " enemies!\n", ({ player, friend }) );
            send_debug_message("mb_ra", player->query_real_name() 
                             + " successfully moves behind " 
                             + friend->query_real_name() + ".");
                             
            on_move_behind_success();
        } 
    }
    else
    {
        player->catch_tell("The enemy onslaught is too overwhelming for "
                         + "you to maneuver.\n");
        send_debug_message("mb_ra", player->query_real_name() 
                         + " fails to moves behind " 
                         + friend->query_real_name() + ".");

        on_move_behind_failure(player);
    }
    
    set_this_player(oldtp);            
}

/*
 * Function name: ability_msg
 * Description  : Mask this function to get a proper prepare message.
 * Arguments    : actor - person doing the attack
 *                targets - list of targets for the attack
 *                args - arguments passed in to do_ability
 * Returns      : nothing
 */
static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object friend;
    
    friend = targets[0];
    actor->catch_msg("You prepare to move behind "
                   + QTNAME(friend) + ".\n");
}

/*
 * Function name: do_ability
 * Description  : The main entry point for abilities
 * Arguments    : arg - the argument passed in for targeting
 * Returns      : 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    string * args;
    string adverb;
    
    if (!stringp(arg))
    {
        notify_fail("Move behind whom [how]?\n");
        return 0;
    }
    
    args = explode(arg, " ");
    if (sizeof(args) < 2
        || args[0] != "behind")
    {
        notify_fail("Move behind whom [how]?\n");
        return 0;    
    }
    
    // Check for an adverb.
    if (sizeof(args) > 2 // with two arguments, no adverbs
        && strlen(adverb = FULL_ADVERB(args[-1..][0])))
    {
        string possible_target = implode(args[1..], " ");
        object * found_targets = PARSE_COMMAND(possible_target, 
            environment(this_player()), "[at] / [on] [the] %l");
        if (!sizeof(found_targets))
        {
            // We only check for adverbs if the full string doesn't
            // match a target.
            args = args[..-2]; // remove the last element
            if (this_player()->query_mb_adverb() != adverb)
            {
                this_player()->calian_set_adverb("move behind " + adverb);
            }
        }
    }
    arg = implode(args[1..], " "); // remove "behind" and combine
    return ::do_ability(arg);
}

public object *
target_friend(object actor, string str)
{
    object *oblist;

    if (!strlen(str))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }
    
    if (Ability_visual || CAN_SEE_IN_ROOM(actor))
    {
        // PARSE_THIS considers darkness.
        oblist = PARSE_THIS(str, "[at] / [on] [the] %l");
    }
    else
    {
        oblist = PARSE_COMMAND(str, environment(actor), "[at] / [on] [the] %l");
    }
    
    if (!sizeof(oblist))
    {
        actor->catch_tell("Whom do you wish to target?\n");
        return ({});
    }

    if (sizeof(oblist) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    return oblist;
}
