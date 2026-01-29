#include "defs.h"
#include <tasks.h>

inherit "/d/Genesis/specials/std/damage";

#define FATIGUE_COST     2
#define HEALTH_COST      5

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

    set_combat_aid(60);
    set_tohit(100);

    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX,
                  SKILL_WEIGHT, 20, TS_WIS }) );
    set_skills( ({ SS_WHIRLWIND }) );
    set_ability_name("whirlwind");

    set_guild_stat_modifier(SS_OCCUP, 20, 100);        
} /* config_ability */


/*
 * Function:    query_ability_prep_time
 * Description: Adjusts the prep time based on guild special skill
 */ 
public int
query_ability_prep_time()
{
    int special_skill;
    
    special_skill = this_player()->query_skill(SS_WHIRLWIND);
    return 8 - (special_skill / 25); // 4-8 seconds
} /* query_ability_prep_time */


/*
 * Function:    query_ability_cooldown_time
 * Description: Adjusts the prep time based on guild special skill
 */ 
public int
query_ability_cooldown_time()
{
    int special_skill;
    
    special_skill = this_player()->query_skill(SS_WHIRLWIND);
    return 8 - (special_skill / 25); // 4-8 seconds
} /* query_ability_cooldown_time */


/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    /* Percentage of combat aid rises from 50% to 100% as skill
     * increases. This is done because the ability time also changes
     * as skill changes. In order to keep the damage the same, we
     * adjust these two factors.
     */
    int special_skill, add_time, aid;
    
    special_skill = this_player()->query_skill(SS_WHIRLWIND);    
    add_time = 4 - (special_skill / 25);
    aid = 400 / (4 + add_time);
    
    return aid;
} /* query_combat_aid_modifier */


/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Typically only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int
query_dt(mixed * items)
{
    return W_SLASH;
} /* query_dt */


/*
 * Function:    check_required_items
 * Description: Checks to make sure that the person has a proper weapon
 *              Used to pass the "items" mixed array
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    object *weapons = actor->query_weapon(-1);

    if (sizeof(weapons) > 1)
    {
        if (weapons[1]->query_wt() != W_SWORD)
            weapons -= ({weapons[1]});
    }
    if (sizeof(weapons))
    {
        if (weapons[0]->query_wt() != W_SWORD)
            weapons -= ({weapons[0]});
    }
    if (!sizeof(weapons))
    {
        actor->catch_msg("You need a sword to a perform a whirlwind!\n");
        return 0;
    }
    
    return weapons;
} /* check_required_items */

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
    object head;
    object player = this_player();
    string a_desc;
    string e_desc;

    switch (phurt)
    {
        case -2:
            a_desc = "but " + HE(enemy) + " parries the attack";
            e_desc = "but you parry the attack";
            break;
        case -1:
            a_desc = "but " + HE(enemy) + " dodges the attack";
            e_desc = "but you dodge the attack";
            break;
        case 0:
            a_desc = "but " + HE(enemy) + " is unharmed";
            e_desc = "but you are unharmed";
            break;
        case 1..4:
            a_desc = "slightly scratching " + HIM(enemy);
            e_desc = "slightly scratching you";
            break;
        case 5..9:
            a_desc = "slicing " + HIM(enemy) + " in many places";
            e_desc = "slicing you in many places";
            break;
        case 10..19:
            a_desc = "slashing "+HIM(enemy)+" badly in many places";
            e_desc = "slashing you badly in many places";
            break;
        case 20..29:
            a_desc = "hacking deep wounds into " + HIS(enemy) + " body";
            e_desc = "hacking deep wounds into your body";
            break;
        case 30..49:
            a_desc = "shredding " + HIM(enemy) +
                " to pieces with unrelenting zeal";
            e_desc = "shredding you to pieces with unrelenting zeal";
            break;
        case 50..69:
            a_desc = "unmercifully hacking " + HIS(enemy) + 
                " body apart like a ruthless butcher";
            e_desc = "unmercifully hacking your body apart like " +
                "a ruthless butcher";
            break;
        case 70..80:
            a_desc = "shredding and hacking " + HIM(enemy) +
                " apart as blood flies everywhere";
            e_desc = "shredding and hacking you apart as "+
                "your blood flies everywhere";
            break;
        default:
            a_desc = "slaughtering " + HIM(enemy) + 
                " like a butcher serving up a carnal feast of " +
                enemy->query_race_name() + " meat";
            e_desc = "slaughtering you like a butcher preparing " +
                "to serve you as the main course";
    }

    if (sizeof(items) > 1)
    {
        player->catch_msg("You leap into the air and come crashing down on " +
            QTNAME(enemy) + " with your blades spinning in a deadly swirl, " +
            a_desc + ".\n");
        enemy->catch_msg(QCTNAME(player) + " leaps into the air and comes " +
            "crashing down on you with " + HIS(player) + " blades spinning " +
            "in a deadly swirl, " + e_desc + ".\n");
        player->tell_watcher(QCTNAME(player) + " leaps into the air and " +
            "comes crashing down on " + QTNAME(enemy) + " with " +
            HIS(player) + " blades spinning in a deadly swirl, " + a_desc +
            ".\n", enemy);
    }
    else
    {
        player->catch_msg("You leap into theh air with your " +
            items[0]->short() + " flash in a wild arcs as you come " +
            "crashing down upon " + QTNAME(enemy) + ", " + a_desc + ".\n");
        enemy->catch_msg(QCTNAME(player) + " leaps into the air with " +
            HIS(player) + " " + items[0]->short() +
            " flashing in wild arcs as " + HE(player) +
            " comes crashing down upon you, " + e_desc + ".\n");
        player->tell_watcher(QCTNAME(player) + " leaps into the air with " +
            HIS(player) + " " + items[0]->short() +
            " flashing in wild arcs as " + HE(player) +
            " comes crashing down upon " + QTNAME(enemy) + ", " + a_desc
            + ".\n", enemy); 
    }

    if (enemy->query_hp() <= 0 && !enemy->query_prop(LIVE_I_NO_CORPSE)
            && !enemy->query_prop(LIVE_I_NO_BODY))
    {
        head = clone_object("/std/leftover");
        head->leftover_init("head", enemy->query_race_name());
        head->move(environment(player), 1);

        player->catch_msg(QCTPNAME(enemy) +
            " head falls off and rolls to your feet!\n");
        enemy->catch_msg("Your head falls off and rolls to "
            + QTPNAME(player) + " feet!\n");
        player->tell_watcher(QCTPNAME(enemy) +
            " head falls off and rolls to " + QTPNAME(player) + " feet!\n",
            enemy);
    } 

    CHECK_DEAD(enemy, player);
        
} /* special_did_hit */


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
    object enemy;
    object * enemies;
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    /* Does attacker have the skill? */
    if (!(player->query_skill(SS_WHIRLWIND)))
    {
        player->catch_tell("You first must learn the whirlwind skill!\n");
        return 0;
    }
    
    /* If it passes everything, return success. */
    return 1; 
} /* check_valid_action */


/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    if (player->query_fatigue() > FATIGUE_COST)
    {
        player->add_fatigue(-FATIGUE_COST);
    }
    else
    {
        player->set_fatigue(0);
    	player->heal_hp(-HEALTH_COST);
    	player->catch_msg("The strain of the attack drains you.\n");        
    }
} /* apply_costs_to_player */


/* HOOKS BELOW */


/*
 * Function name: hook_stun_fail
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stun_fail(object ability)
{
    this_player()->catch_tell("You are too stunned to use your"
      + " whirlwind attack!\n");
} /* hook_stun_fail */


/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("You feel ready to perform a whirlwind attack again!\n");
} /* hook_special_complete */



