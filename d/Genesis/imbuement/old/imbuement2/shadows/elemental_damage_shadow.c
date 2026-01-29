/*
 *  /d/Genesis/imbuement/shadows/elemental_damage_shadow.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  elemental damage to a weapon.
 *
 *  Created November 2009 by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_BASE;

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>

/* Definitions */
#define EXTRA_PEN        16

/* Global Variables */
public int               Power_Level = 1;
public string            Resistance_Type = "";
public string            Ss_Type = "";
public string           *Hit_Descs = allocate(5);
public string           *Damage_Msgs = allocate(2);

/* Prototypes */
public void              elemental_strike(object enemy, string hit_loc = "body");
public varargs int       did_hit(int aid, string hdesc, int phurt,
                                 object enemy, int dt, int phit, int dam);
public void              init_imbue_shadow(int lvl);
public int               query_elemental_pen(int lvl);
public int               combine_resistances(object target, string *resistances);

public void              set_resistance_type(string s) { Resistance_Type = s; }
public void              set_ss_type(string s) { Ss_Type = s; }
public void              set_hit_descs(string *s) { Hit_Descs = s; }
public void              set_damage_msgs(string *s) { Damage_Msgs = s; }


/*
 * Function name:        burn_enemy
 * Description  :        a special attack for this weapon based on the
 *                       fire-based mod it has been given.
 * Arguments    :        object enemy - the person we are attacking 
 *                       string hit_loc - what body part we struck.
 */
public void
elemental_strike(object enemy, string hit_loc = "body")
{
    string  strike,
            how;
    int     dam = 0,
            pen,
            res;
    mixed   rval;
    object  item_owner = environment(shadow_who);

    if (!objectp(enemy) ||
        !objectp(item_owner))
    {
        return;
    }

    pen = query_elemental_pen(Power_Level) + random(EXTRA_PEN);
    res = combine_resistances(enemy,
                           ({ Resistance_Type, MAGIC_I_RES_MAGIC }) );
    pen -= pen * res / 100;

    rval = enemy->hit_me(F_PENMOD(
               pen, 100),
               MAGIC_DT, item_owner, -1);

    if (pointerp(rval))
    {
        dam = rval[0];
    }

    switch (pen)
    {
        case  0..8:
            strike = Hit_Descs[0];
            break;
        case  9..12:
            strike = Hit_Descs[1];
            break;
        case 13..16:
            strike = Hit_Descs[2];
            break;
        case 17..20:
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

    item_owner->catch_msg(capitalize(Damage_Msgs[0]) + " your "
      + shadow_who->short() + " and " + strike + " the " + hit_loc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + how + " by the " + Damage_Msgs[1] + ".\n");

    enemy->catch_msg(capitalize(Damage_Msgs[0]) + " "
      + QTNAME(item_owner) + "'s " + shadow_who->short() + " and " + strike
      + " your " + hit_loc + "!\n"
      + "You are " + how + " by the " + Damage_Msgs[1] + ".\n");

    item_owner->tell_watcher(capitalize(Damage_Msgs[0]) + " "
      + QTNAME(item_owner) + "'s " + shadow_who->short() + " and " + strike
      + " the " + hit_loc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + how
      + " by the " + Damage_Msgs[1] + ".\n", enemy);

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
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy,
                                       dt, phit, dam);

    TELL_G("did_hit called! phurt = " + phurt);

    if (!objectp(enemy))
    {
        return (rval);
    }

    /* The damage done by the flame attack is not determined by the
     * Power_Level of the imbuement. Rather, the frequency of the
     * flame attack occuring increases with the Power_Level.
     */
    if (phurt > 0 &&
        !random(IMBUE_SPECIAL_STRIKE_RATE))
    {   
        TELL_G("Trying to do a special!"); 
        set_alarm(0.0, 0.0, &elemental_strike(enemy, hdesc));
    }
    else
    {
        TELL_G("No special this time.");
    }

    return (rval);
} /* did_hit */


/*
 * Function name:        init_imbue_shadow
 * Description  :        Called when the shadow is first moved to the
 *                       item so that certain processes can be begun
 *                       and initializations set.
 * Arguments    :        int lvl - the power level of the imbuement.
 *                                 Range: 1-3
 */
public void
init_imbue_shadow(int lvl)
{   
    ::init_imbue_shadow(lvl);

    Power_Level = lvl;
} /* init_imbue_shadow */


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


/*
 * Function name: combine_resistances
 * Description:   Sometimes spells are resisted by more than
 *                one type of resistance (typically MAGIC_I_RES_MAGIC and
 *                MAGIC_I_RES_<element>).  This function returns a composite
 *                resistance value for a target, given a list of resistance
 *                types to check.
 * Arguments:     object target - the object to check for resistance
 *                string resistances - the resistance types to check
 * Returns:       The total resistance
 *
 * Special thanks to Petros for this function!
 */
public int
combine_resistances(object target, string *resistances)
{
    int i, res = 100;

    for (i = 0; i < sizeof(resistances); i++)
    {
        res = res * (100 - target->query_magic_res(resistances[i])) / 100;
    }

    if (res >= 0)
    {
        res = 100 - res;
    }

    return res;
} /* combine_resistances */
