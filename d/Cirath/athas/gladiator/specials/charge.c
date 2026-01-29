/*
 * Port of the Gladiator Charge to the new specials system
 *
 * Created by Petros, August 2008
 */

#pragma strict_types

#include "../defs.h"

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"

#define CHARGE_FATIGUE   3
#define CHARGE_HP        10

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public void             apply_costs_to_player(object player);
public int              force_fail(object player, mixed * items, 
                                   object enemy, int resist, int result);

// Global Variables

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
    set_combat_aid(70);
    set_tohit(90); // 82% chance to hit.
    set_dt(W_BLUDGEON);
    // Extra damage taken from Strength and Constitution and Discipline
    set_stats(({ SKILL_AVG, TS_STR, TS_CON, TS_DIS, SKILL_END }) );
    set_skills(({ SS_CHARGE }) );
    // Can charge once every 18 seconds on average
    set_ability_prep_time(8);
    set_ability_cooldown_time(10);
    set_ability_name("charge");
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the actor has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required, or 0 if a required item is
 *                missing.
 */
static mixed * check_required_items(object actor,
                    mixed * targets,string arg,int pretest)
{
    mixed * weapons;
    object best_axe;
    int max_pen = 40;
    weapons = actor->query_weapon(-1);
    if (pointerp(weapons))
    {
        foreach (object weapon : weapons)
        {
            if (weapon->query_wt() == W_AXE
                && weapon->query_pen() > max_pen)
            {
                best_axe = weapon;
                max_pen = weapon->query_pen();
            }
        }
    }
    
    if (max_pen > 40)
    {
        return ({ best_axe });
    }
    
    // Otherwise, just return an empty array. that way, it'll
    // default to 40 pen.
    return ({ });
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
    object player, weapon;
    mixed hit_descr;
    string how, chargestr;

    player = this_player();
    chargestr = MANAGER->query_charge_desc(player);
    
    if (phurt >= 0)
    {
        player->add_panic(- phurt / 5);
        if (enemy->query_hp() > 0)
        {
            switch (phurt)
            {
            case 0:
                how = "amazed by such a feeble attack";
                break;
            
            case 1..15:
                how = "dazed";
                break;
            
            case 16..30:
                how = "injured";
                break;
            
            case 31..50:
                how = "hurt";
                break;
            
            case 51..75:
                how = "hurt";
                break;
            
            default:
                how = "on the verge of collapse";
            } 
    
            player->catch_msg("You strike "+QTNAME(enemy)+" with "+
              "your "+chargestr+".\n");
            player->catch_msg(QCTNAME(enemy)+" looks "+ how +".\n");
    
            enemy->catch_msg(QCTNAME(player) + " strikes you with "+
              HIS_HER(player) + " "+chargestr+".\n");
            enemy->catch_tell("You feel " + how + ".\n");
    
            player->tell_watcher(QCTNAME(player)+" strikes " +
              QTNAME(enemy) + " with " + HIS_HER(player) + " " +
              chargestr+".\n", enemy);
    
            return;
        }
    
        // The gladiator has killed his/her enemy
        player->catch_msg("Bones break and blood splatters as you "+
          "devastate " + QTNAME(enemy) + " with your "+chargestr+
          ", throwing "+HIM_HER(enemy)+" to the ground in a "+
          "bloody, lifeless heap.\n");
    
        player->tell_watcher(QCTNAME(enemy) + " lets out a final shriek in "+
          "horrible agony and falls lifelessly to the "+
          "ground at the feet of " + QTNAME(player) + ".\n", enemy);
    
        enemy->do_die(player);
        return;
    }
    else
    {
        // Missed!
        player->add_panic(2);
    
        player->catch_msg("You miss " + QTNAME(enemy) + " completely "+
          "with your "+chargestr+".\n");
    
        enemy->catch_msg(QCTNAME(player) + " flails wildly past you, "+
          "missing miserably with "+HIS_HER(player)+" "+chargestr+".\n");
    
        player->tell_watcher(QCTNAME(player) + " runs past " + QTNAME(enemy) +
          " in a botched attempt to hit "+HIM_HER(enemy) + ".\n", enemy);
    }
}

/*
 * Function name: validate_charge_requirements
 * Description  : Function to check all the prerequisites of charge
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_charge_requirements(object player)
{
    setuid();
    seteuid(getuid()); 
    if (CHECK_PUNISHMENT(player, PUN_EXPEL))
    {
        player->catch_tell("By Kalak's decree a gladiator expelled "
                        + "by the Overseers may not charge.\n");
        send_debug_message("charge", 
                           capitalize(player->query_real_name()) 
                         + " not allowed to charge.");
        return 0;
    }    

    /* Does attacker have the skill? */
    if (!(player->query_skill(SS_CHARGE)))
    {
        player->catch_tell("First you should learn how.\n");
        return 0;
    }

    if (CHECK_PUNISHMENT(player, PUN_SPEC))
    {
        player->catch_tell("Kalak has cursed you with the inability to "
                         + "charge!\n" +
                           "You shall need to find another way to defeat "
                         + "your enemies.\n");
        return 0;
    }

    return 1;
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
    object enemy;
    object * enemies;
    
    if (!validate_charge_requirements(player))
    {
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

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
    if (player->query_fatigue() > CHARGE_FATIGUE)
    {
        player->add_fatigue(-CHARGE_FATIGUE);
    }
    else
    {
        player->set_fatigue(0);
        player->reduce_hit_points(CHARGE_HP);
        player->catch_tell("The strain of the attack drains you.\n");
    }
}

/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason. Called right before execution at the end
 *                of the delay
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
public int 
force_fail(object player, mixed * items, object enemy, 
           int resist, int result)
{
    if (!validate_charge_requirements(player))
    {
        return 1;
    }

    return 0;
}

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability,object player)
{
    // Don't display any messages
}

/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("\nYou feel ready to crush your foe again.\n\n");   
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
    write("You abandon your charge as your foe is no longer present.\n");
    hook_special_complete();
}

static void 
ability_msg(object actor,mixed * targets,string arg)
{
    write("You prepare to execute the lethal attack.\n");
}
