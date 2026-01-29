/*
 * This is a draconian soldier. 
 */

/* March 23 2006, Navarre added check for objectp
 * in the hit_me function, as it caused a runtime
 * exception.
 *
 * May 9th 2006, Navarre added check for missile weapon
 *               when weapons are trapped in the stone.
 *               Bows shouldn't be trapped!
 *
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "draconian.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

inherit DRACONIAN;

static object *gBaaz_inv, gLast_weapon;
static int gLast_id;

/*
 * Function name: set_baaz_skills
 * Description:   Calc and set the stats and skills for the draconian.
 */
nomask static void
set_baaz_skills()
{
    int i, level;

    for (i = 0; i < 6; i++) /* 21 - 39 */
        set_base_stat(i, (random(4) + 1) * 3 + 18 + random(10));

    level = query_draconian_level();

    set_skill(SS_DEFENCE,     level * 6 + random(20) + 3);
    set_skill(SS_PARRY,       level * 6 + random(8) + 3);
    set_skill(SS_WEP_SWORD,   level * 6 + random(8) + 3);
    set_skill(SS_WEP_KNIFE,   level * 6 + random(8) + 3);
    set_skill(SS_WEP_CLUB,    level * 6 + random(8) + 3);
    set_skill(SS_WEP_POLEARM, level * 6 + random(8) + 3);
    set_skill(SS_WEP_JAVELIN, level * 6 + random(8) + 3);
    set_skill(SS_WEP_AXE,     level * 6 + random(8) + 3);
    set_skill(SS_AWARENESS,   level * 5);

    set_draconian_alignment();
}

/*
 * Function name: create_baaz
 * Description:
 */
public void
create_baaz()
{
}

/*
 * Function name: create_draconian
 * Description:
 */
nomask public void
create_draconian()
{
    set_baaz_skills();
    set_draconian_type(BAAZ);

    create_baaz();

    add_name("baaz");

    set_exp_factor(105);
    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(OBJ_I_RES_ACID, 50);    

/*
    add_act("emote flaps its wings.");
    add_act("emote looks suspiciously around.");
*/
}

/*
 * Function name: do_draconian_die
 * Description:   This happens when a Baaz dies.
 * Arguments:     killer - The object who killed it
 */
public void
do_draconian_die(object killer)
{
    gBaaz_inv = all_inventory(TO);
}

/*
 * Function name: hit_me
 * Description:   Get the id of the object that hit us. Then call the
 *                original hit_me.
 * Arguments:     wcpen       - The wc-penetration
 *                dt          - damagetype, use MAGIC_DT if ac will not
 *                              help against this attack.
 *                attacker    - Object hurting us
 *                attack_id   - Special id saying what attack hit us. If you
 *                              have made a special attack, let the id be -1
 * Returns:       The hitresult as given by the external combat object.
 */
public mixed 
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    gLast_id = attack_id;

    if (attack_id >= 0 && objectp(attacker))
    {
        gLast_weapon = attacker->query_weapon(attack_id);
        gLast_id = attack_id;
    }
    else
        gLast_weapon = 0;

    return (::hit_me(wcpen, dt, attacker, attack_id));
}

/*
 * Function name: second_life
 * Description:
 * Arguments:     killer - 
 * Returns:
 */
public int
second_life(object killer)
{
    object statue, wep;
    string wep_sh;

    set_alarm(0.0, 0.0, remove_object);

    tell_room(E(TO), "The draconian turns into stone!\n");

    statue = clone_object(STATUE);
    gBaaz_inv->move(statue, 1);
    statue->move(E(TO));
    wep = killer->query_weapon(gLast_id);

    if ((wep == gLast_weapon) && !wep->query_prop(OBJ_I_IS_MAGIC_WEAPON) &&
        (wep->weapon_type()!="missile weapon") &&
        (wep->query_dt() & W_SLASH || wep->query_dt() & W_IMPALE))
    {
        if (random(killer->query_stat(SS_DEX)) > random(60))
        { 
      	    killer->catch_msg("Just at the last moment are you able to " +
                "pull your " + wep->short() + " free.\n");
            return 0;
        }

        set_this_player(killer);
        wep->unwield_me();

        if (wep->move(statue) == 0)
        {
            killer->catch_msg("Oh no! The weapon is stuck in the " +
                "stone!\n");

            wep_sh = wep->short();
            tell_watcher(QCTNAME(killer) + " lets go of " +
                killer->query_possessive() + " " + wep_sh +
                ", since it got stuck in the stone.\n", killer);
                killer->catch_msg("You let go of your " + wep_sh + ".\n");
            return 0;
        }
    }   

    return 0;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
