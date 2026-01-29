/*
 * Army of Angmar retreat ability.
 * The ability utilizes minor functions found in the Calian Move Behind ability.
 * - reattack_object
 * - stopattack_object
 *
 * Coded by Carnak at 2018-03-23, requested by Gorboth.
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include "../guild.h"

inherit "/d/Genesis/specials/timed_ability";

// Prototypes
public object *target_unspecific_team(object actor, string str);

/*
 * Function name:   config_ability
 * Description:     Main fuction that configures what the special should look
 *                  like.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_ability_visual(0);
    set_ability_name("retreat");
    set_ability_offensive(0);
    set_ability_prep_time(0);
    set_ability_cooldown_time(6);
    
    set_ability_target(target_unspecific_team);
} /* config_ability */

/*
 * Function name:   do_ability
 * Description:     The main entry point for abilities
 * Arguments:       (string) arg - the argument passed in for targeting
 * Returns:         (int) 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    string *args;
    
    if (this_player()->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    if (strlen(arg))
    {
        args = explode(arg, " ");
        
        if (sizeof(args) < 2 || args[0] != "behind")
        {
            notify_fail("Retreat behind whom?\n");
            return 0;
        }
        
        // remove "behind" and combine
        arg = implode(args[1..], " ");
    }
    
    return ::do_ability(arg);
} /* do_ability */

/*
 * Function name:   target_unspecific_team
 * Description:     Handles the targetting if we dont specify a target.
 * Arguments:       1. (object) actor - The actor of the ability
 *                  2. (string) str - The arguments
 * Returns:         (object *) - The singular target encapsulated in array
 */
public object *
target_unspecific_team(object actor, string str)
{
    object target;
    
    /* If we dont specify a target, try to move behind a random team member */
    if (!strlen(str))
    {
        target = one_of_list(target_present_team_others(actor, str));
        
        if (!objectp(target))
            return ({});
            
        return ({ target });
	}
    
    return target_one_other_present_living(actor, str);
} /* target_unspecific_team */


/* 
 * Function name:   reattack_object 
 * Description:     Called to make an enemy re-attack someone who has been moved 
 *                  behind. 
 * Arguments:       1. (object) enemy   - the person attacking 
 *                  2. (object) target  - the person attacked 
 * Returns:         Nothing
 */ 
public void 
reattack_object(object enemy, object target) 
{ 
    enemy->stop_fight(target); 
    enemy->attack_object(target); 
} /* reattack_object */

/* 
 * Function name:   stopattack_object 
 * Description:     Called to make an enemy stop fighting someone who moves 
 *                  behind in a ROOM_M_NO_ATTACK room. 
 * Arguments:       1. (object) enemy   - the person attacking 
 *                  2. (object) actor   - the person who moved behind 
 *                  3. (object) target  - person who is now in front 
 * Returns:         Nothing
 */ 
public void 
stopattack_object(object enemy, object actor, object target) 
{ 
    enemy->stop_fight(actor);
    actor->stop_fight(enemy);
    
    if (target->query_attack() == enemy)
    { 
        enemy->stop_fight(target);
        enemy->attack_object(target);
    }
} /* stopattack_object */

/*
 * Function name:   query_retreat_success
 * Description:     Gives the result of whether the retreat attempt is
 *                  successful or not. It uses resolve_task to perform the
 *                  opposed check.
 * Arguments:       1. (object)   actor   - player trying to move behind
 *                  2. (object)   target  - target of the move behind
 *                  3. (object *) enemies - enemies attacking the player
 * Returns:         (int) 0/1 - failure/success
 */
public int
query_retreat_success(object actor, object target, object *enemies)
{
    object attacker; // a random attacker from list of enemies
    int target_modifier, enemy_modifier, mb_skill, last_time;
    
    // We will use resolve_task to determine success
    // Task:   move behind a target when being attacked
    // Calian    : Dex, Wisdom, Int, Move Behind skill
    //             target's str, target's dis
    // Attackers : Dex, Wisdom, Number of Attackers * 20
    // We need to determine success.

    mb_skill = actor->query_skill(SS_RETREAT);
    // If a person cannot see, we modify their mb_skill by the
    // blindfighting skill
    if (!CAN_SEE_IN_ROOM(actor))
    {
        int blind_skill = actor->query_skill(SS_BLIND_COMBAT);
        mb_skill = max(min(5, mb_skill), mb_skill * blind_skill / 100);
    }
        
    attacker = enemies[random(sizeof(enemies))]; 
    enemy_modifier = sizeof(enemies) * 20;
    target_modifier = (target->query_stat(SS_STR) 
                       + target->query_stat(SS_DIS)) / 2;

    if (actor->resolve_task(TASK_EASY, 
               ({ SS_RETREAT,
                  SKILL_WEIGHT, mb_skill,
                  SKILL_AVG, TS_DEX, TS_WIS, TS_INT, SKILL_END,
                  SKILL_VALUE, target_modifier }),
                  attacker,
                  ({ TS_DEX, TS_WIS, SKILL_VALUE, enemy_modifier })) >= 0)
    {
        // If we reached the task number of TASK_EASY, this is a success.
        return 1;
    }            
    
    return 0;
} /* query_retreat_success */

/*
 * Function name:   check_valid_action
 * Description:     Perform ability-specific checks
 * Arguments:       1. (object) actor - The player
 *                  2. (mixed *) targets - The targets
 *                  3. (string) arg - Arguments passed to the command
 *                  4. (int) execute - Actual spell execution
 * Returns:         (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed * targets, string arg, int execute)
{
    object target, *enemies, *carried, *team;
    
    if (actor->query_skill(SS_RETREAT) < 1)
    {
        actor->catch_msg("You rack your brain, but fail to find a way to "
        + "retreat.\n");
        return 0;
    }
    
    // Get the target, with some redundancy
    if (!objectp(target = targets[0]))
    {
        actor->catch_msg("Retreat behind whom?\n");
        return 0;
    }
    
    // Shouldnt happen, but redundancy doesnt hurt
    if (target == actor)
    {
        actor->catch_msg("How could you possibly retreat behind yourself?\n");
        return 0;
    }
    
    // Lets verify that they are in the same room
    if (environment(actor) != environment(target))
    {
        actor->catch_msg("Retreat behind whom?\n");
        return 0;
    }
    
    // For redundancy, verify that it is not a non-living
    if (!living(target))
    {
        actor->catch_msg("How do you expect hiding behind " + target->short()
        + " is going to keep you safe?\n");
        return 0;
    }
    
    // To prevent people from attacking themselves
    if (target->query_attack() == actor)
    {
        actor->catch_msg("You can't retreat behind someone who is attacking "
        + "you!\n");
        return 0; 
    }
    
    carried = filter(all_inventory(actor), &operator(==)(,actor) @
              &->query_attack());
    enemies = filter(all_inventory(environment(actor)), &operator(==)(,actor) @
              &->query_attack());
    
    // Display a message when only attempting to retreat from inventory enemies.
    if (sizeof(carried) && !sizeof(enemies))
    { 
        actor->catch_msg("You can't get away from something you are "
        + "carrying!\n"); 
        return 0;
    }
    
    // No enemies to move away from
    if (!sizeof(enemies))
    {
        actor->catch_msg("Retreat from whom?\n");
        return 0;
    }
    
    // Can only retreat behind team members
    if (!sizeof(team = actor->query_team_others()))
    {
        actor->catch_msg("You are not a member of a team.\n");
        return 0;
    }
    
    // Target is not a team member
    if (member_array(target, team) < 0)
    {
        actor->catch_msg(actor->query_The_name(target) + " is not a member of "
        + "your team.\n");
        return 0;
    }
    
    return 1;
} /* check_valid_action */

/*
 * Function name:   ability_msg
 * Description:     Mask this function to get a proper prepare message.
 * Arguments:       1. (object) actor - person doing the attack
 *                  2. (mixed *) targets - list of targets for the attack
 *                  3. (string) args - arguments passed in to do_ability
 * Returns:         Nothing
 */
static void 
ability_msg(object actor, mixed * targets, string arg)
{
    //actor->catch_msg("You prepare to retreat behind "
    //+ targets[0]->query_the_name(actor) + ".\n");
} /* ability_msg */

/* 
 * Function name:   resolve_ability
 * Description:     Called to execute the ability after all the checks have been
 *                  done.
 * Arguments:       1. (object)  actor   - person executing the special
 *                  2. (mixed *) items   - array from check_required_items
 *                  3. (mixed *) targets - array of targets for this special
 *                  4. (int *)   resist  - the list of resistances
 *                  5. (mixed *) result  - the list of results, one per target
 * Returns:         Nothing
 */ 
static void 
resolve_ability(object actor, mixed * items, 
                mixed * targets, int * resist, mixed * results)
{
    object *enemies,
            target;
    int     msg_num = 0;
    
    target  = targets[0];
    enemies = filter(all_inventory(environment(actor)), &operator(==)(,actor) @
              &->query_attack());
    
    /* Use a less violent version of the retreat for morgul mages, non-members
     * and members of higher rank.
     */
    if (target->query_guild_name_occ() == "Morgul Mages" || !IS_MEMBER(target)
        || AA_RANKS_OBJ->rank_no(target) >= AA_RANKS_OBJ->rank_no(actor))
        msg_num = 1;
        
    if (query_retreat_success(actor, target, enemies))
    {
        if (environment(actor)->query_prop(ROOM_M_NO_ATTACK))
            map(enemies, &stopattack_object(,actor, target));
        else
            map(enemies, &reattack_object(,target));
        
        actor->catch_msg(({
            "You haul " + target->query_the_name(actor) + " forward and kick "
            + "them roughly to the front of the action!\n",
            "Taking too much heat, you cry out to "
            + target->query_the_name(actor) + " and then move aside as they "
            + "rush to the front of the action!\n"
        })[msg_num]);
        
        target->catch_msg(({
            actor->query_The_name(target) + " grabs you and hauls you in front "
            + "of " + actor->query_objective() + ". With a rough kick in your "
            + "back, you are launched to the front of the action!\n",
            actor->query_The_name(target) + " cries out to you, taking too "
            + "much heat. " + capitalize(actor->query_pronoun()) + " falls "
            + "back as you rush to the front of the action!\n"
        })[msg_num]);
        
        actor->tell_watcher(({
            QCTNAME(actor) + " turns and hauls " + QTNAME(target) + " forward. "
            + "With a rough kick to the backside, " + QTNAME(target) + " is "
            + "propelled to the front of the action!\n",
            QCTNAME(actor) + ", taking too much heat, cries out to "
            + QTNAME(target) + ". " + capitalize(actor->query_pronoun())
            + " falls back as " + QTNAME(target) + " rushes to the front of "
            + "the action!\n"
        })[msg_num], ({ target }));
        
        actor->set_last_retreat(time());
        actor->set_retreat_target(target);
        return;
    }
    
    actor->catch_msg(({
        "You explode into profanities as you discover that "
        + target->query_the_name(actor) + " has moved too far away from you in "
        + "the heat of battle.\n",
        "You are taking too much heat and find yourself unable to retreat "
        + "behind " + target->query_the_name(actor) + ".\n"
    })[msg_num]);
    
    target->catch_msg(({
        actor->query_The_name(target) + " explodes into profanities as "
        + actor->query_pronoun() + " discovers that you have moved too far "
        + "away from " + actor->query_objective() + " in the heat of "
        + "battle.\n",
        actor->query_The_name(target) + " appears to be taking too much heat "
        + "and unable to retreat behind you.\n"
    })[msg_num]);
    
    actor->tell_watcher(({
        QCTNAME(actor) + " explodes into profanities as "
        + actor->query_pronoun() + " discovers that " + QTNAME(target) + " has "
        + "moved too far away in the heat of battle.\n",
        QCTNAME(actor) + " appears unable to retreat behind " + QTNAME(target)
        + " due to the heavy onslaught.\n"
    })[msg_num], ({ target }));
} /* resolve_ability */

/*
 * Function name:   hook_already_active
 * Description:     Mask this function to get a message for when the ability is
 *                  active.
 * Arguments:       1. (object) ability - The ability that is active
 * Returns:         Nothing
 */
public void
hook_already_active(object ability)
{
    write("You are already preparing your retreat!\n");
} /* hook_already_active */

/*
 * Function name:   hook_special_in_cooldown
 * Description:     Mask this function to get a custom message for when the
 *                  ability is in cooldown.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    write("You are still too far out in front. You begin to maneuver yourself "
    + "into a suitable position to retreat again.\n");
} /* hook_special_in_cooldown */