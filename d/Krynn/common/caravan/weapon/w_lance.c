
/*
 *  Filename:       w_lance.c
 *  Description:    A lance for knights riding the caravan
 *
 *
 *  Copyright (c) Nov. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Commerce part taken from other place done by Boron.

 *  Change log:
 *  January 2004 - downgraded to fit new balance rule for 1 handers.
 */


inherit "/std/weapon";
inherit "/d/Genesis/lib/commodity";


#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"
#define SS_WOLF_RIDING 135001

#define HIT 35
#define PEN 35

int mounted = 0;
string steed;

public void
create_weapon()
{
    set_name("lance");
    add_name(({"weapon","polearm"}));
    set_pname("lances");
    add_pname(({"polearms","weapons"}));
    set_adj("ornamented");
    add_adj("long");
    set_short("long ornamented lance");
    set_pshort("long ornamented lances");
    set_long("This is a lance of majestic proportions, " +
      "long and strong, truly worthy the Solamnian Knights " +
      "who favour it. Its length stretches "+
      "longer than a man, and the tip is sharpened to a point, the lance " +
      "is decorated with ornaments all along the length of it. " +
      "Along the hilt, a small inscription is carved.\n");
    set_default_weapon(HIT, PEN, W_POLEARM, W_IMPALE, W_LEFT);

    add_prop(MAGIC_AM_MAGIC, ({ 35, "enchantment" }) );

    set_commodity_name ("w_lance"); // required to link this
                                  // object with the domain server
    set_commodity_value(F_VALUE_WEAPON(HIT,PEN), 0);

    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN));

    add_prop(OBJ_S_WIZINFO, "This lance works much better if the wielder " +
        "is mounted, it will give extra hit depending on the wielders skill " +
        "in polearm, and give more penetration depending on the wielders  " +
        "skills in riding, animal handling, wolf riding and mounted combat " +
        "skill.\n");
    add_prop(MAGIC_AM_ID_INFO, ({
        "The lance was created for jousting contests and blessed " +
        "to do more damage than normal while mounted.\n", 10,
        "The unmounted will gain nothing from the lance.\n" , 20,
        "The ones skilled in mounted combat will be specially gifted " +
        "by the lance.\n " , 65 }) );


    set_wf(TO);

}


/*
 * Function name: unwield
 * Description:   Called when the weapon is unwielded, masking it to
 *                ensure the weapon got the crappiest hit/pen.
 * Arguments:     what:  The weapon unwielded
 */

int
unwield(object what)
{
    set_hit(HIT);
    set_pen(PEN);
    query_wielded()->update_weapon(TO);

    return 0;
}

/*
 * Function name: calc_hit
 * Description:   Calculates the weapons to hit if mounted.
 *
 * Arguments:     none
 * Return value:  The hit value between 36 and 46.
 */

int
calc_hit()
{
    /* returns between 35 and 46 in hit of the weapon while mounted */
    return MIN(HIT + (wielder->query_skill(SS_WEP_POLEARM) / 10) + 1, 46) ;
}

/*
 * Function name: calc_pen
 * Description:   Calculates the weapons pen if mounted.
 *
 * Arguments:     none
 * Return value:  The pen value between 36 and 56.
 */

int
calc_pen()
{
    int skill;
    /* returns between 35 and 50 in penetration  */

    skill = wielder->query_skill( SS_ANI_HANDL) ;
    skill += MAX(wielder->query_skill( SS_RIDING),
                 wielder->query_skill( SS_WOLF_RIDING))  * 2 ;
    skill += wielder->query_skill( SS_MOUNTED_COMBAT) * 3 ;


    return MIN(PEN + skill / 25, 50) ;
}

/*
 * Function name: state_change
 * Description:   Resets the weapons hit/pen whenever there is a
 *                change in being mounted or not.
 *
 * Arguments:     hit : the new hit
 *                pen : the new pen
 */

void
state_change(int hit, int pen)
{

    set_hit(hit);
    set_pen(pen);

    if (wielded && wielder)
        wielder->update_weapon(this_object());
//    DEBUG_MSG ("NEW HIT: " + hit + " PEN: " + pen);
}

/*
 * Function name: did_hit
 * Description:   Masks the did_hit function to give better
 *                combatmessages while mounted, and to test
 *                if there's a change in the mounted situation
 *
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                dam:   The actual damage caused by this weapon in hit points
 *                hid:   The hitlocation id
 * Returns:       True if it handled combat messages, returning a 0 will let
 *                the normal routines take over */


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r;
    string tmp;
    string wound_adj;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if ( wielder->query_steed())
    {

        /* Switch to high power */
        if (!mounted)
        {
            state_change(calc_hit(), calc_pen());
            mounted = 1;
            steed = wielder->query_steed()->steed_short();

        }

        tmp = hdesc;
        if (tmp == 0)
            tmp = "body";

    switch (phurt)
    {
    case -2..-1:
        return 0;
    case 0..4:
        wielder->catch_msg("You barely hit the " + tmp + " of " +
             QTNAME(enemy) + " with the tip of your " + short() + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " barely hits your " + tmp +
            " with the tip of " + POSSESSIVE(wielder) + " " + short() + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " barely hits the " + tmp +
            " of " + QTNAME(enemy) + " with the tip of " + POSSESSIVE(wielder) +
            " " + short() + ".\n", enemy);
    break;
    case 5..19:
        wound_adj = ({ "shallow", "light", "minor", "mediocre" })[random(4)];

        wielder->catch_msg("While riding by " + QTNAME(enemy) +
            " you open a " + wound_adj + " wound in the " +
            tmp + " of " + HIM(enemy) + ".\n");
        enemy->catch_msg("As " + QCTNAME(wielder) + " rides by you, " +
            HIS(wielder) + " " + short() + " opens a " + wound_adj  +
            " wound in your " + tmp + ".\n");
        wielder->tell_watcher("As " + QCTNAME(wielder) + " rides by " +
            QTNAME(enemy) + ", " + HE(wielder) + " opens a " + wound_adj +
            " wound in " + HIS(enemy) + " " + tmp +  ".\n" ,enemy);
    break;
    case 20..30:
        wound_adj = ({ "shallow", "grave", "deep",
            "piercing" })[random(4)];

        wielder->catch_msg("You spin around the " + steed +
            " and hits " + QTNAME(enemy) + " with a quick blow from the side" +
            ", inflicting a " + wound_adj + " wound.\n");
        enemy->catch_msg(QCTNAME(wielder) + " spins the " + steed +
            " around and hits you with a quick blow from the side, " +
            "inflicting a " + wound_adj + " wound.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " spins the " +
            steed + " around and hits "+  QTNAME(enemy) +
            " with a quick blow from the side, inflicting a " +
            wound_adj + " wound.\n",  enemy);
    break;
    case 31..55:
        wielder->catch_msg("You spur your " + steed + " forward " +
            "into a charge, and wounds " + QTNAME(enemy) +
            " with your " + short() + ", gashing " + HIS(enemy) + " " + tmp +
            " deeply.\n");
        enemy->catch_msg(QCTNAME(wielder) + " spurs the " + steed +
            " forward and wounds you with " + HIS(wielder) + " " + short() +
            ", gashing your " + tmp + " deeply.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " spurs the " +
            steed + " forward and wounds " + QTNAME(enemy)
            + " with " + HIS(wielder) + " " + short() + ", gashing " +
            HIS(enemy) + " " + tmp + " deeply.\n",enemy);
    break;
    case 56..68:
        wound_adj = ({ "bleeding", "serious", "deep",
            "badly looking" })[random(4)];

        wielder->catch_msg("Digging the heels into the sides of the " +
            steed + ", you rush forward with your " + short() +
            " lowered, making a " + wound_adj + " wound into the " + tmp +
            " of " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " digs " +
            HIS(wielder) + " heels into the sides of the " + steed +
            " lowering the " + short() + " causing a " + wound_adj +
            " wound into the " + tmp + " of you.\n");
        wielder->tell_watcher(QCTNAME(wielder) + " digs " +
            HIS(wielder) + " heels into the sides of the " + steed +
            " lowering the " + short() + " causing a " + wound_adj +
            " wound into the " + tmp + " of " + QCNAME(enemy) +".\n", enemy );
    break;
    case 69..88:
        wielder->catch_msg("Charging directly at " + QTNAME(enemy) +
            " you bury the " + short() + " deep into " + HIS(enemy) +
            " " + tmp  + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " charges directly at you " +
            "burying " + HIS(wielder) + " " +short() +
            " deep into your " + tmp + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " charges directly at " +
            QTNAME(enemy) + " burying " + HIS(wielder) + " " + short() +
            " deep into " + QTNAME(enemy) + "'s " + tmp + ".\n", enemy );

    break;
    default:
        wielder->catch_msg("Charging directly at " + QTNAME(enemy) +
            " you bury the " + short() + " deep into " + HIS(enemy) +
            " " + tmp  + ".\n");
        enemy->catch_msg(QCTNAME(wielder) + " charges directly at you " +
            "burying " + HIS(wielder) + " " +short() +
            " deep into your " + tmp + ".\n");
        wielder->tell_watcher(QCTNAME(wielder) + " charges directly at " +
            QTNAME(enemy) + " burying " + HIS(wielder) + " " + short() +
            " deep into " + QTNAME(enemy) + "'s " + tmp + ".\n" , enemy);

    break;

    }
    return 1;
    }
    else
    {
 //       DEBUG_MSG ("I AM NOT MOUNTED");
        /* Switch to low power */
        if (mounted)
        {
            state_change(HIT, PEN);
            mounted = 0;
        }

    }

    return r;
}