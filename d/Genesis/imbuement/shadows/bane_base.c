/*
 *  /d/Genesis/imbuement/shadows/bane_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  give damage to certain races.
 *
 *  2010/09/12 Lavellan, based on elemental_damage_shadow by Gorboth
 *
 *  Modification log:
 *    - added living() check to prevent rare fights with corpses (Gorboth)
 *
 * 2021-04-04 - Cotillion
 * - Fixed triggering on parry
 *  
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";


#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>      //for IS_PLAYER_OBJECT

/* Definitions */

/* Global Variables */
public string           *Races = ({ "foo" });
public string            Ss_Type = "";
public string           *Hit_Descs = allocate(5);
public string            Damage_Msg = "lemming";
public int               Recharge_Alarm = 0;
public object            oldwf;

/* Prototypes */
public void              race_damage(object enemy, int attack_id, int hit_id, int off_vs_def);
public varargs int       did_hit(int aid, string hdesc, int phurt,
                            object enemy, int dt, int phit, int dam, int hit_id);
public varargs int       got_hit(int hid, int ph, object att, int dt, int dam,
                            int hit_id);
public void              check_race(object enemy, int attack_id, int hit_id, int off_vs_def);
public void              init_imbue_shadow(int lvl);
public int               query_elemental_pen(int lvl);
public void              set_races(string * s) { Races = s; }
public void              set_ss_type(string s) { Ss_Type = s; }
public void              set_hit_descs(string *s) { Hit_Descs = s; }
public void              set_damage_msg(string s) { Damage_Msg = s; }
public void              charge();
public mixed             wield(object obj);
public mixed             wear(object obj);
public mixed             unwield(object obj);
public mixed             remove(object obj);


/*
 * Function name:        race_damage
 * Description  :        a special attack for this that only fires against
 *                       certain races
 * Arguments    :        object enemy - the person we are attacking 
 *                       int attack_id - what made the hit
 *                       int hit_id - what body part we struck.
 */
public void
race_damage(object enemy, int attack_id, int hit_id, int off_vs_def)
{
    string  strike,
            how,
            hit_loc;
    int     dam = 0,
            pen,
            res;
    mixed   rval;
    object  item_owner = environment(shadow_who);
    string  pow = "object's strange power";
    object  strike_obj;
    string  strike_str;

    if (!objectp(enemy) ||
        !living(enemy) ||
        !objectp(item_owner))
    {
        return;
    }

    pen = query_elemental_pen(query_imbuement_power_level()) + random(IMBUE_BANE_PEN_EXTRA);

    /* We make sure pen is between 10 - 66 */
    pen = max(10, min(66, pen));
    
    int adjusted_pen = F_PENMOD(pen, 100);
    res = "/d/Genesis/specials/resist"->combine_resistances(enemy,
                           ({ MAGIC_I_RES_FIRE, MAGIC_I_RES_MAGIC }) );
    adjusted_pen -= adjusted_pen * res / 100;

    // One final modification to pen is to match non-magic calculation inside
    // of cb_hit_me, using F_NEW_DAMAGE formula. We multiply the resistance by 80%
    // and make that the chance that the pen goes to 0
    if (random(100) < (res * 80 / 100))
    {
        adjusted_pen = 0;
    }

    if (enemy == item_owner)
        rval = enemy->hit_me(adjusted_pen,
            MAGIC_DT, shadow_who, -1, hit_id);
    else
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
        // If bow, we attribute to projectile if possible
        if (shadow_who->query_stringed() && enemy != item_owner)
        {
            strike_obj = shadow_who->query_projectile_stack();
            if (objectp(strike_obj))
            {
                strike = "your " + strike_obj->singular_short() + " " +
                    strike;
            }
            else
            {
                if (IS_BOW_OBJECT(shadow_who))
                {
                    strike = "your arrow " + strike;       
                }
                else
                {
                    strike = "your projectile " + strike;
                }
            }
        }
        else
        {
            strike_obj = shadow_who;
        }
        strike_str = shadow_who->short();
    }
    else if (IS_UNARMED_ENH_OBJECT(shadow_who))
    {
        strike_obj = shadow_who;
        strike_str = strike_obj->short();
        if (enemy != item_owner && !off_vs_def)
        {
            strike = "your " + item_owner->cr_attack_desc(attack_id) +
                " " + strike;
        }
    }
    else
    {
        strike_obj = shadow_who;
        strike_str = strike_obj->short();
    }

    if (enemy == item_owner)
    {
        item_owner->catch_msg(capitalize(Damage_Msg) + " the "
          + strike_str + " and " + strike + " your " + hit_loc
          + "!\nYou are " + how + " by the " + pow + ".\n");

        item_owner->tell_watcher(capitalize(Damage_Msg) + " "
          + QTNAME(item_owner) + "'s " + strike_str + " and " + strike
          + " " + item_owner->query_possessive() + " " + hit_loc + "!\n"
          + capitalize(item_owner->query_pronoun()) + " looks " + how
          + " by the " + pow + ".\n", item_owner);
    }
    else
    {
        item_owner->catch_msg(capitalize(Damage_Msg) + " your "
          + strike_str + " and " + strike + " the " + hit_loc
          + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
          + " looks " + how + " by the " + pow + ".\n");

        enemy->catch_msg(capitalize(Damage_Msg) + " "
          + QTNAME(item_owner) + "'s " + strike_str + " and " + strike
          + " your " + hit_loc + "!\n"
          + "You are " + how + " by the " + pow + ".\n");

        item_owner->tell_watcher(capitalize(Damage_Msg) + " "
          + QTNAME(item_owner) + "'s " + strike_str + " and " + strike
          + " the " + hit_loc + " of " + QTNAME(enemy) + "!\n"
          + capitalize(enemy->query_pronoun()) + " looks " + how
          + " by the " + pow + ".\n", enemy);
    }

    if (IS_PLAYER_OBJECT(item_owner) && IS_PLAYER_OBJECT(enemy))
        IMBUE_LOGGER->log("pvp", sprintf("%s by %s  %d (%d%%)  %s/%s (%d)",
            capitalize(enemy->query_real_name()),
            capitalize(item_owner->query_real_name()),
            rval[3], rval[0],
            "bane-" + Races[0],
            shadow_who->short(),
            query_id()));

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(item_owner);
    }
} /* race_damage */


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
 * This is masked to apply the random chance for a race-limited special attack.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
    int dam, int hid)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy,
                                       dt, phit, dam, hid);

    check_race(enemy, aid, hid, 0);
    return rval;
} /* did_hit */


public varargs int
got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    int     rval = shadow_who->got_hit(hid, ph, att, aid, dt, dam);

    if (ph < 0)
        return rval;

    check_race(att, aid, hid, 1);
    return rval;
} /* got_hit */


/*
 * Function name:        check_race
 * Description  :        check race of enemy and do attack if correct
 * Arguments    :        object enemy - the person attacking/attacked
 *                       int attack_id - what made the hit
 *                       int hit_id - what body part we struck.
 */
public void
check_race(object enemy, int attack_id, int hit_id, int off_vs_def)
{
    int go = 0;

    if (!objectp(enemy))
    {
        return;
    }

    send_debug_message("Shadows", "check_race called! race = " +
        enemy->query_race_name());

    if (member_array(enemy->query_race_name(), Races) >= 0)
    {
        go = 1;
    }

    if ((Races[0] == "undead") && (enemy->query_prop(LIVE_I_UNDEAD)))
    {
        go = 1;
    }

    if (!go)
    {
        send_debug_message("Shadows", "Wrong race.");
        return;
    }

    if (off_vs_def)
    {
        if (get_alarm(Recharge_Alarm))
        {
            send_debug_message("Shadows", "No charge.");
        }
        else
        {
            Recharge_Alarm = set_alarm(20.0, 0.0, charge);
            set_alarm(0.0, 0.0, &race_damage(enemy, attack_id, hit_id, off_vs_def));
        }
    }
    else
    {
        if (random(100) < IMBUE_SPECIAL_STRIKE_RATE)
        {   
            send_debug_message("Shadows", "Trying to do a special!"); 
            set_alarm(0.0, 0.0, &race_damage(enemy, attack_id, hit_id, off_vs_def));
        }
        else
        {
            send_debug_message("Shadows", "No special this time.");
        }
    }

} /* check_race */


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

    Races = this_object()->query_races();
    oldwf = shadow_who->query_wf();
    shadow_who->set_wf(this_object());
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
} /* query_elemental_pen */


/*
 * Function name:        charge
 * Description  :        Called by alarm for armours when power is charged
 */
public void
charge()
{
    Recharge_Alarm = 0;
} /* charge */


/*
 * Function name:        wield
 * Description  :        Prevent wielding if subject to bane
 * Returns      :        mixed - It could be wielded or not
 */
public mixed
wield(object obj)
{
    mixed res = oldwf->wield(obj);

    if (stringp(res)) return res;
    if (member_array(environment(shadow_who)->query_race_name(), Races) >= 0)
    {
        race_damage(environment(shadow_who), -1, -1, 0);
        return "It doesn't seem safe to wield that!\n";
    }

    return res;
} /* wield */


/*
 * Function name:        wear
 * Description  :        Prevent wear if subject to bane
 * Returns      :        mixed - It could be wielded or not
 */
public mixed
wear(object obj)
{
    mixed res = oldwf->wear(obj);

    if (stringp(res)) return res;
    if (member_array(environment(shadow_who)->query_race_name(), Races) >= 0)
    {
        race_damage(environment(shadow_who), -1, -1, 1);
        return "It doesn't seem safe to wear that!\n";
    }

    return res;
} /* wear */


/*
 * Function name:        unwield
 * Description  :        Nothing, just call routine from wearer.
 * Returns      :        mixed - Result from original routine
 */
public mixed
unwield(object obj)
{
    return oldwf->unwield(obj);
} /* unwield */


/*
 * Function name:        remove
 * Description  :        Nothing, just call routine from wearer.
 * Returns      :        mixed - Result from original routine
 */
public mixed
remove(object obj)
{
    return oldwf->remove(obj);
} /* remove */

/*
 * Function:    query_formation_type
 * Description: Each bane imbuement shadow has a type of formation that emits
 *              a particular flow. Each one should override this one and
 *              specify a type of formation that forms along the surface.
 */
public string
query_formation_type()
{
    return "non-sensical";
}

/*
 * Function:    query_imbued_indication
 * Description: This is the custom message that gets displayed on an imbued
 *              item to help identify what the particular imbuement is on
 *              the item. It is usually displayed as a part of the "long"
 *              description of the item when examined.
 *              Each imbuement base class should customize this.
 * Returns:     A string that should be displayed to the user when examining
 *              an imbued item. A newline will automatically be added at the
 *              end of the long description.
 */
public string
query_imbued_indication()
{
    return capitalize(query_formation_type()) + " formations along its "
      + "surface emit " + LANG_ADDART(POWER_DESC[Power_Level]) + " glow.";
}

