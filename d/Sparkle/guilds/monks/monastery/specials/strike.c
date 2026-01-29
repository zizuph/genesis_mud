/*
 * This is a modernization of the Monk special to
 * use the standard damage combat special library.
 *
 * Combat descriptions lifted from original Monk
 * special combat code by Arandir.
 *
 * Created by Ckrik, July 2015
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

public void config_ability()
{
    ::config_ability();
    set_combat_aid(200);
    set_tohit(75);
    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX,
                  SKILL_WEIGHT, 20, TS_DIS })
    );
    set_skills(({ M_SKILL_STRIKE }) );

    set_ability_time(10);
    set_dt(W_BLUDGEON);
    set_ability_name("strike");
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
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

string get_strike_attack(object oStriker)
{
    string *asAttacks;
    // We can not hold a weapon in our legs ...
    asAttacks = ({ M_DESC_FOOT_LEFT, M_DESC_FOOT_RIGHT });
    // If we are not wielding anything in both hands, we can be
    // wielding something in either hand ...

    if (!objectp(oStriker->query_weapon(W_BOTH)))
    {
        if (!objectp(oStriker->query_weapon(W_LEFT)))
        {
            asAttacks += ({ M_DESC_FIST_LEFT });
        }
        if (!objectp(oStriker->query_weapon(W_RIGHT)))
        {
            asAttacks += ({ M_DESC_FIST_RIGHT });
        }
    }
    // Now just return a random attack.
    return one_of_list(asAttacks);
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

void strike_message(object oStriker, object oTarget, int iPHurt, string sHitLoc,
    int iPHit, int iDamage)
{
    string sWeapon = get_strike_attack(oStriker);
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
                    oStriker->query_possesive() + " feet"
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
        oStriker->query_possesive() + " " + sWeapon + ".\n");
    oTarget->tell_watcher(sPrefixOthers + QTPNAME (oTarget) + " " + sHitLoc +
        " with " + oStriker->query_possesive() + " " + sWeapon + ".\n", oStriker);
}

public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, object * items, int result)
{
    object tp = this_player();

    strike_message(tp, enemy, phurt, hdesc, phit, dam);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_player());
    }    
}

