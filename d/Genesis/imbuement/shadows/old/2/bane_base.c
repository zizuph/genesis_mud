/*
 *  /d/Genesis/imbuement/shadows/bane_base.c
 *
 *  This shadow is inherited by all imbuement shadows that add
 *  give damage to certain races.
 *
 *  2010/09/12 Lavellan, based on elemental_damage_shadow by Gorboth
 */
#pragma strict_types
#include "../imbuement.h"

inherit SHADOW_DIR + "imbuement_shadow";


#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>

/* Definitions */
//#define EXTRA_PEN        16

/* Global Variables */
public int               Power_Level = 1;
public string           *Races = ({ "foo" });
public string            Ss_Type = "";
public string           *Hit_Descs = allocate(5);
public string            Damage_Msg = "lemming";

/* Prototypes */
public void              race_damage(object enemy, string hit_loc = "body",
                                int arm = 0);
public varargs int       did_hit(int aid, string hdesc, int phurt,
                                 object enemy, int dt, int phit, int dam);
//public varargs int       got_hit(int hid, int ph, object att, int dt, int dam);
public void              check_race(object enemy, string hdesc, int arm);
public void              init_imbue_shadow(int lvl);
public int               query_elemental_pen(int lvl);
public void              set_races(string * s) { Races = s; }
public void              set_ss_type(string s) { Ss_Type = s; }
public void              set_hit_descs(string *s) { Hit_Descs = s; }
public void              set_damage_msg(string s) { Damage_Msg = s; }


/*
 * Function name:        race_damage
 * Description  :        a special attack for this that only fires against
 *                       certain races
 * Arguments    :        object enemy - the person we are attacking 
 *                       string hit_loc - what body part we struck.
 */
public void
race_damage(object enemy, string hit_loc = "body", int arm = 0)
{
    string  strike,
            how;
    int     dam = 0,
            pen,
            res;
    mixed   rval;
    object  item_owner = environment(shadow_who);
    string  pow = (arm ? "armour's strange power" : "weapon's strange power");

    if (!objectp(enemy) ||
        !objectp(item_owner))
    {
        return;
    }

    pen = query_elemental_pen(Power_Level) + random(IMBUE_BANE_PEN_EXTRA);
    res = "/d/Genesis/newmagic/spell"->combine_resistances(enemy,
                           ({ MAGIC_I_RES_FIRE, MAGIC_I_RES_MAGIC }) );
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

    item_owner->catch_msg(capitalize(Damage_Msg) + " your "
      + shadow_who->short() + " and " + strike + " the " + hit_loc
      + " of " + QTNAME(enemy) + "!\n" + capitalize(enemy->query_pronoun())
      + " looks " + how + " by the " + pow + ".\n");

    enemy->catch_msg(capitalize(Damage_Msg) + " "
      + QTNAME(item_owner) + "'s " + shadow_who->short() + " and " + strike
      + " your " + hit_loc + "!\n"
      + "You are " + how + " by the " + pow + ".\n");

    item_owner->tell_watcher(capitalize(Damage_Msg) + " "
      + QTNAME(item_owner) + "'s " + shadow_who->short() + " and " + strike
      + " the " + hit_loc + " of " + QTNAME(enemy) + "!\n"
      + capitalize(enemy->query_pronoun()) + " looks " + how
      + " by the " + pow + ".\n", enemy);

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
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    int     rval = shadow_who->did_hit(aid, hdesc, phurt, enemy,
                                       dt, phit, dam);

    check_race(enemy, hdesc, 0);
    return(rval);
} /* did_hit */


public varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    int     rval = shadow_who->got_hit(hid, ph, att, dt, dam);
    string *locs = ({});
    object  cobj = att->query_combat_object();
    foreach (int loc : cobj->query_hitloc_id())
    {
        locs += ({ cobj->cb_hitloc_desc(loc) });
    }
    check_race(att, one_of_list(locs), 1);
    return(rval);
} /* got_hit */


/*
 * Function name:        check_race
 * Description  :        check race of enemy and do attack if correct
 * Arguments    :        object enemy - the person attacking/attacked
 *                       string hdesc - what body part we struck.
 */
public void
check_race(object enemy, string hdesc, int arm)
{
    int go = 0;

    TELL_G("check_Race called! race = " + enemy->query_race());

    if (!objectp(enemy))
    {
        return;
    }

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
        TELL_G("Wrong race.");
        return;
    }

//    if (phurt > 0 &&
    if (!random(IMBUE_SPECIAL_STRIKE_RATE))
    {   
        TELL_G("Trying to do a special!"); 
        set_alarm(0.0, 0.0, &race_damage(enemy, hdesc, arm));
    }
    else
    {
        TELL_G("No special this time.");
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
} /* query_elemental_pen */
