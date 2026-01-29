/*
 * This is a modernization of the Monk special to
 * use the standard damage combat special library.
 *
 * Combat descriptions lifted from original Monk
 * special combat code by Arandir.
 *
 * Created by Ckrik, July 2015
 * 
 * Updated by Ckrik 11/18/2021
 *     Restored ability to pick hitloc at standard penalty rate.
 * 
 */
#pragma strict_types

#include "defs.h"

inherit DAMAGE_LIB;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "/std/combat/combat.h"

#define M_DIR_NONE              0
#define M_DIR_HIGH_TO_LOW       1
#define M_DIR_HIGH_TO_HIGH      2
#define M_DIR_LOW_TO_LOW        3
#define M_DIR_LOW_TO_HIGH       4

#define M_DESC_FOOT_RIGHT       "right foot"
#define M_DESC_FOOT_LEFT        "left foot"
#define M_DESC_FIST_RIGHT       "right fist"
#define M_DESC_FIST_LEFT        "left fist"
#define M_DESC_ERROR            "mind"

public void config_ability()
{
    ::config_ability();
    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX,
                  SKILL_WEIGHT, 20, TS_DIS })
    );
    set_skills(({ M_SKILL_STRIKE }) );

    set_ability_time(10);
    set_dt(W_BLUDGEON);
    set_ability_name("mstrike");
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
    // We override the fatigue cost from 2 to 1 because
    // Monks have 2 fast acting specials.
    player->add_fatigue(-1);
}

int get_strike_attack_id(object oStriker)
{
    // We can not hold a weapon in our legs ...
    int *iAttackIds = ({ W_FOOTR, W_FOOTL });
    // If we are not wielding anything in both hands, we can be
    // wielding something in either hand ...
    if (!objectp(oStriker->query_weapon(W_BOTH)))
    {
        if (!objectp(oStriker->query_weapon(W_LEFT)))
        {
            iAttackIds += ({ W_LEFT });
        }
        if (!objectp(oStriker->query_weapon(W_RIGHT)))
        {
            iAttackIds += ({ W_RIGHT });
        }
    }
    return one_of_list(iAttackIds);
}

string get_strike_attack(int iAttackId)
{
    switch (iAttackId)
    {
    case W_LEFT: return M_DESC_FIST_LEFT;
    case W_RIGHT: return M_DESC_FIST_RIGHT;
    case W_FOOTL: return M_DESC_FOOT_LEFT;
    case W_FOOTR: return M_DESC_FOOT_RIGHT;
    default: return M_DESC_ERROR;
    }
}

int get_strike_direction(string sWith, string sWhere)
{
    if ((sWith == "left fist") || (sWith == "right fist"))
    {
        // From high
        if (sWhere == "legs")
        {
            return M_DIR_HIGH_TO_LOW;
        }
        else
        {
            return M_DIR_HIGH_TO_HIGH;
        }
    }
    else
    {
        // From low
        if (sWhere == "legs")
        {
            return M_DIR_LOW_TO_LOW;
        }
        else
        {
            return M_DIR_LOW_TO_HIGH;
        }
    }
}

/*
 * Function name: check_required_items
 * Description  : 
 * Returns      : items that are required.
 */
static mixed *
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    object *shields = filter(actor->query_armour(-1),
        &operator(==)(A_SHIELD) @ &->query_at());
    int attack_id = get_strike_attack_id(actor);

    // Disable strike when wearing 2 shields
    if (sizeof(shields) >= 2)
    {
        actor->catch_msg("Your wearing the " + shields[0]->query_short() + " and " +
            shields[1]->query_short() + " prevent you from executing your strike.\n");
        return 0;
    }
    
    // Only 50% effectiveness available when wearing 1 shield.
    // Enforced at query_modified_pen() below.
    if (sizeof(shields) == 1)
    {
        actor->catch_msg("Your wearing " + shields[0]->query_short() +
            " hinder you from executing your strike effectively.\n");
    }

    return ({ attack_id });
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
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }

    // TODO: to the extent that punishment disables the special, check
    // here

    // If it passes everything, return success
    return 1;
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
    // No op
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
    write("You abandon your strike as your target is no longer present.\n");
    hook_special_complete();
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int query_combat_aid_modifier()
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    object tp = this_player();
    int modifier = 100;

    // For each shield worn we reduce the pen by 50%
    // Wearing two shields -> 0 pen

    object *shields = filter(tp->query_armour(-1),
        &operator(==)(A_SHIELD) @ &->query_at());
    modifier -= sizeof(shields) * 50;
    if (modifier < 0)
    {
        modifier = 0;
    }

    return modifier;
}

string translate_hitloc (string sHitloc)
{
    string sResult;
    string sSide;

    sResult = sHitloc;

    if (sResult == "")
    {
        sResult = "body";
    }
    if (sResult == "legs")
    {
        sResult = (random(2) ? "left" : "right") + " leg";
    }

    if ((sResult == "head") && !random(5))
    {
        sResult = random(2) ? "face" : "throat";
    }
    if ((sscanf (sHitloc, "%s arm", sSide) == 1) && !random(2))
    {
        sResult = random (2) ? "lower " + sResult : sSide + " shoulder";
    }
    if ((sscanf (sHitloc, "%s leg", sSide) == 1) && !random(2))
    {
        sResult = random(2) ? "lower " + sResult : sSide + " thigh";
    }
    if ((sResult == "body") && !random(2))
    {
        sResult = random(2) ? "chest" : "stomach";
    }

    return (sResult);
}

void strike_message(object oStriker, object oTarget, int iPHurt, int iAttackId, string sHitLoc,
    int iPHit, int iDamage)
{
    string sWeapon = get_strike_attack(iAttackId);
    int iPrefix;
    string sPrefixHim = "";
    string sPrefixOthers = "";
    string sHitHim;
    string sHitOthers;

    // On humanoids, we can recognize directions of the strikes.
    if (oTarget->query_humanoid())
    {
        switch (get_strike_direction(sWeapon, sHitLoc))
        {
        case M_DIR_HIGH_TO_LOW:
            iPrefix = random(4);
            sPrefixHim = (({
                "Executing a quick roll on the ground",
                "With a quick downward jab",
                "Crouching down",
                "Ducking down"
            })) [iPrefix];
            sPrefixOthers = (({
                "Executing a quick roll on the ground",
                "With a quick downward jab",
                "Crouching down",
                "Ducking down"
            })) [iPrefix];
        break;
        case M_DIR_HIGH_TO_HIGH:
            iPrefix = random (2);
            sPrefixHim = (({
                "Spinning around",
                "Executing a deft spin on the balls of your feet"
            })) [iPrefix];
            sPrefixOthers = (({
                "Spinning around",
                "Executing a deft spin on the balls of " +
                    oStriker->query_possessive() + " feet"
            })) [iPrefix];
        break;
        case M_DIR_LOW_TO_LOW:
            iPrefix = random (2);
            sPrefixHim = (({
                "With a sweeping motion",
                "Dropping to the ground"
            })) [iPrefix];
            sPrefixOthers = (({
                "With a sweeping motion",
                "Dropping to the ground"
            })) [iPrefix];
        break;
        }
    }
    // Make the hitloc description a tad prettier.
    sHitLoc = translate_hitloc(sHitLoc);
    // See about the strength of the hit.
    iPHurt = MAX(-1, iPHurt);
    switch (iPHurt)
    {
    case -1:
        sHitHim = "miss";
        sHitOthers = "misses";
    break;
    case 0..2:
        sHitHim = "brush";
        sHitOthers = "brushes";
    break;
    case 3..4:
        sHitHim = "bruise";
        sHitOthers = "bruises";
    break;
    case 5..9:
        if ((sWeapon == M_DESC_FOOT_RIGHT) || (sWeapon == M_DESC_FOOT_LEFT))
        {                 
            sHitHim = "kick";       sHitOthers = "kicks";
        }
        else
        {
            sHitHim = "punch";      sHitOthers = "punches";
        }
    break;
    case 10..19:
        sHitHim = "strike";
        sHitOthers = "strikes";
    break;
    case 20..29:
        sHitHim = "slam";
        sHitOthers = "slams";
    break;
    case 30..49:
        sHitHim = "smash";
        sHitOthers = "smashes";
    break;
    default:
        sHitHim = "crush";
        sHitOthers = "crushes";
    break;
    }
    // Now just put it all together.
    if (strlen (sPrefixHim))
    {
        sPrefixHim += ", you " + sHitHim + " ";
        sPrefixOthers += ", " + QTNAME(oStriker) + " " + sHitOthers + " ";
    }
    else
    {
        sPrefixHim = "You " + sHitHim + " ";
        sPrefixOthers = QTNAME(oStriker) + " " + sHitOthers + " ";
    }

    oStriker->catch_msg(sPrefixHim + QTPNAME (oTarget) + " " + sHitLoc +
        " with your " + sWeapon + ".\n");
    oTarget->catch_msg(sPrefixOthers + "your " + sHitLoc + " with " +
        oStriker->query_possessive() + " " + sWeapon + ".\n");
    oTarget->tell_watcher(sPrefixOthers + QTPNAME (oTarget) + " " + sHitLoc +
        " with " + oStriker->query_possessive() + " " + sWeapon + ".\n", oStriker);
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
public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items, int result)
{
    object tp = this_player();
    int strike_attack_id;

    if (sizeof(items) > 0 && intp(items[0]))
    {
        strike_attack_id = items[0];
    }
    else
    {
        strike_attack_id = get_strike_attack_id(tp);
    }
    strike_message(tp, enemy, phurt, strike_attack_id, hdesc, phit, dam);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_player());
    }    
}
