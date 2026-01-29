/*
 * Cadet Donk Special
 *
 * This is the special for Cadets guild, which has been ported to
 * use the Genesis specials system.
 *
 * Ported by Petros, June 2009
 */

#pragma strict_types

#include "defs.h"
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/damage";

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(50); // laymans max out at 50% combat aid
    // We don't want to modify the values downward based on the
    // person's stat. The reason is that Cadets are generally very
    // small, and this would end up always lowering their level.
    set_stats(({ SKILL_VALUE, 100 }) );
    // Can donk once every 16 seconds
    set_ability_prep_time(4);
    set_ability_cooldown_time(12);
    set_ability_name("donk");
    
    set_guild_stat_modifier(SS_OCCUP, 30, 50);    
}

public mixed
query_skills()
{
    object player;
    // For Cadets, their donk is dependent on the skill of the
    // weapon that they are using.
    // Donk will always use the weapon that they are most
    // skilled in.
    
    player = this_player();
    int * weapon_skills = map(player->query_weapon(-1), &->query_wt());
    if (!sizeof(weapon_skills))
    {
        weapon_skills = ({ SS_UNARM_COMBAT });
    }

    int max_skill = applyv(max, map(weapon_skills, player->query_skill));
    int * best_skills = filter(weapon_skills, &operator(==)(max_skill) 
                                               @ player->query_skill);
    // We weight the skill by 9/5 in order to match the old donk skill
    // increase.                                           
    return ({ SKILL_WEIGHT, 180, player->query_skill(best_skills[0]) });
}

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 *                items - 
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items, int result)
{
 
}

/*
 * Function name: check_required_items
 * Description  : Look for an axe or club
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    return 0;
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 *                Neidar have no fatigue penalty for using their special.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player) 
{
    // Cadets don't get weary when using donk
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
    int donk_ban = player->query_skill(SS_CADET_DONK_BAN); 
    if (donk_ban) 
    { 
        if (donk_ban > time()) 
        { 
            player->catch_tell("You have been banned from donking " 
                + "until " + ctime(donk_ban) + ".\n"); 
        } 
        else 
        { 
            player->remove_skill(SS_CADET_DONK_BAN); 
        } 
    } 
    
    return ::check_valid_action(player, targets, arg, execute);    
}

// HOOKS DEFINED BELOW

/*
 * Function:    hook_special_complete
 * Description: This hook informs the player when they are able to
 *              execute their special again.
 */
public void 
hook_special_complete()
{
    write("You are ready to donk again!\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: When a player tries to execute the special while it is in
 *              cooldown, this hook gets called.
 */
public void
hook_special_in_cooldown()
{
//	write("Patience! You have not yet recovered from your last attack!\n");
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object * targets)
{
    object * alive;
    
    alive = filter(targets, objectp);
    if (sizeof(alive))
    {
        write("You lost your donk target!\n");
    }
    else
    {
        write("You relax as you realize your that your donk target is "
            + "no longer a threat anymore.\n");
    }
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    object target = targets[0];
    actor->catch_msg("You prepare to dork " + QTNAME(target) + ".\n");
}
