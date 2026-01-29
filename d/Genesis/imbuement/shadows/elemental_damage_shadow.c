/*
 *  /d/Genesis/imbuement/shadows/elemental_damage_shadow.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  elemental damage to a weapon.
 *
 *  Created November 2009 by Cooper Sherry (Gorboth)
 *
 *  Updated Jan 2022 by Ckrik
 *      - Allow unarmed enhancers and bows.
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>      //for IS_PLAYER_OBJECT

/* Definitions */
#define EXTRA_PEN        16

/* Global Variables */
public string            Resistance_Type = "";
public string            Ss_Type = "";
public string           *Hit_Descs = allocate(5);
public string           *Damage_Msgs = allocate(2);

/* Prototypes */
public void              elemental_strike(object enemy, int attack_id, int hit_id);
public varargs int       did_hit(int aid, string hdesc, int phurt,
                            object enemy, int dt, int phit, int dam, int hit_id);
public int               query_elemental_pen(int lvl);

public void              set_resistance_type(string s) { Resistance_Type = s; }
public void              set_ss_type(string s) { Ss_Type = s; }
public void              set_hit_descs(string *s) { Hit_Descs = s; }
public void              set_damage_msgs(string *s) { Damage_Msgs = s; }


/*
 * Function name:        elemental_strike
 * Description  :        a special attack for this weapon based on the
 *                       element-based mod it has been given.
 * Arguments    :        object enemy - the person we are attacking 
 *                       int attack_id - what tool slot
 *                       int hit_id - what body part we struck.
 */
public void
elemental_strike(object enemy, int attack_id, int hit_id)
{
    string  strike,
            how,
            hit_loc;
    int     dam = 0,
            pen,
            res;
    mixed   rval;
    object  item_owner = environment(shadow_who);
    object  strike_obj;
    string  strike_str;

    if (!objectp(enemy) ||
        !objectp(item_owner))
    {
        return;
    }

    pen = query_elemental_pen(query_imbuement_power_level()) + random(EXTRA_PEN);
    /* We make sure pen is between 10 - 66 */
    pen = max(10, min(66, pen));

    int adjusted_pen = F_PENMOD(pen, 100);
    res = "/d/Genesis/specials/resist"->combine_resistances(enemy,
                           ({ Resistance_Type, MAGIC_I_RES_MAGIC }) );
    adjusted_pen -= adjusted_pen * res / 100;

    // One final modification to pen is to match non-magic calculation inside
    // of cb_hit_me, using F_NEW_DAMAGE formula. We multiply the resistance by 80%
    // and make that the chance that the pen goes to 0
    if (random(100) < (res * 80 / 100))
    {
        adjusted_pen = 0;
    }

    rval = enemy->hit_me(adjusted_pen,
               MAGIC_DT, item_owner, -1, hit_id);

    if (pointerp(rval))
    {
        dam = rval[0];
        hit_loc = (rval[1] ? rval[1] : "soul");
    }
    else
        return;

    switch (adjusted_pen)
    {
        case  0..139:
            strike = Hit_Descs[0];
            break;
        case 140..186:
            strike = Hit_Descs[1];
            break;
        case 187..273:
            strike = Hit_Descs[2];
            break;
        case 274..348:
            strike = Hit_Descs[3];
            break;
        default:
            strike = Hit_Descs[4];
            break;
    }

    switch (dam)
    {
        case  -1..0:
            how = "unharmed";
            break;
        case   1..5:
            how = "slightly hurt";
            break;
        case  6..10:
            how = "somewhat hurt";
            break;
        case 11..20:
            how = "hurt";
            break;
        case 21..30:
            how = "rather hurt";
            break;
        case 31..50:
            how = "very hurt";
            break;
        default:
            how = "badly hurt";
            break;
    }

    if (IS_LAUNCH_OBJECT(shadow_who))
    {
        // If bow, we attribute to projectile
        strike_obj = shadow_who->query_projectile_stack();
        if (!objectp(strike_obj))
        {
            strike_obj = shadow_who;
            strike_str = strike_obj->short();
        }
        else
        {
            strike_str = strike_obj->singular_short();
        }

        // If bow, we attribute to projectile if possible
        if (shadow_who->query_stringed())
        {
            strike_obj = shadow_who->query_projectile_stack();
            if (objectp(strike_obj))
            {
                strike_str = strike_obj->singular_short();
            }
            else
            {
                if (IS_BOW_OBJECT(shadow_who))
                {
                    strike_str = "arrow ";       
                }
                else
                {
                    strike_str = "projectile";
                }
            }
        }
        else
        {
            strike_obj = shadow_who;
            strike_str = strike_obj->short();
        }
    }
    else if (IS_UNARMED_ENH_OBJECT(shadow_who))
    {
        strike_obj = shadow_who;
        strike_str = item_owner->cr_attack_desc(attack_id);
    }
    else
    {
        strike_obj = shadow_who;
        strike_str = strike_obj->short();
    }

    item_owner->catch_msg(capitalize(Damage_Msgs[0]) + " your "
      + strike_str + " and " + strike + " the " + hit_loc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + how + " by the " + Damage_Msgs[1] + ".\n");

    enemy->catch_msg(capitalize(Damage_Msgs[0]) + " "
      + QTNAME(item_owner) + "'s " + strike_str + " and " + strike
      + " your " + hit_loc + "!\n"
      + "You are " + how + " by the " + Damage_Msgs[1] + ".\n");

    item_owner->tell_watcher(capitalize(Damage_Msgs[0]) + " "
      + QTNAME(item_owner) + "'s " + strike_str + " and " + strike
      + " the " + hit_loc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + how
      + " by the " + Damage_Msgs[1] + ".\n", enemy);

    if (IS_PLAYER_OBJECT(item_owner) && IS_PLAYER_OBJECT(enemy))
        IMBUE_LOGGER->log("pvp", sprintf("%s by %s  %d (%d%%)  %s/%s (%d)",
            capitalize(enemy->query_real_name()),
            capitalize(item_owner->query_real_name()),
            rval[3], rval[0],
            "damage-" + Resistance_Type[13..],
            strike_str,
            query_id()));

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(item_owner);
    }
} /* elemental_strike */


/*
 * Function name: did_hit
 * Description:   Tells us that we hit something. Should produce combat
 *                messages to all relevant parties. If the weapon
 *                chooses not to handle combat messages then a default
 *                message is generated.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over
 * 
 * This is masked to apply the random chance for a fire attack.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
    int dam, int hid)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy,
                                       dt, phit, dam, hid);

    send_debug_message("Shadows", "did_hit called! phurt = " + phurt);

    if (!objectp(enemy))
    {
        return (rval);
    }

    /* The damage done by the flame attack is not determined by the
     * Power_Level of the imbuement. Rather, the frequency of the
     * flame attack occuring increases with the Power_Level.
     */
    if (phurt > 0 &&
        (random(100) < IMBUE_SPECIAL_STRIKE_RATE))
    {   
        send_debug_message("Shadows", "Trying to do a special!"); 
        set_alarm(0.0, 0.0, &elemental_strike(enemy, aid, hid));
    }
    else
    {
        send_debug_message("Shadows", "No special this time.");
    }

    return (rval);
} /* did_hit */

/*
 * Function name:        query_elemental_pen
 * Description  :        Determine the amount of elemental penetration
 *                       damage that can be done by this specific
 *                       imbuement
 * Returns      :        int - the chance (in terms of %)
 */
public int
query_elemental_pen(int lvl)
{
    switch (lvl)
    {
        case 1:
            return IMBUE_ELEMENTAL_PEN_LOW;
            break;
        case 2:
            return IMBUE_ELEMENTAL_PEN_MED;
            break;
        case 3:
            return IMBUE_ELEMENTAL_PEN_HIGH;
            break;
        default:
            return 0;
            break;
    }

    return 0; /* should never happen, but just in case. */
} /* imbue_power_chance */
