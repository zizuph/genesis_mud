/* 
 * Shadow of brass knuckles used by lowly Brix gangers behind
 * Jems court in the Aesthetics quarter of Palanthas.
 *
 * Based on the coding concept behind Shiva's flaming knuckles
 * found on Lyden in Tyr.
 *
 * It detects wielding/unwielding of weapons and unarmed attacks,
 * calling the appropriate functions in the knuckles.
 *
 * Mortis 05.2006
 *
 * Allowed weapons to be used but not shields. Mortis 9.2014
 *
 * These have been reviewed by AoB and returned to blocking weapons
 * due to thematic discrepancies, the knuckles affected the damage of
 * bludgeon weapons.
 *
 * Carnak 02.2016
 *
 * Ported over to use unarmed_enhancers.
 *
 * Ckrik 11.2021
 */

inherit "/std/shadow";

#include <wa_types.h>

static object knuckles;

void
remove_knuckles_shadow()
{
    remove_shadow();
}

int
query_knuckles_shadow() {return 1;}

void
set_knuckles_ob(object ob) {knuckles = ob;}

object
query_knuckles_ob() {return knuckles;}

/* This is called when the wearer tries to wield a weapon.
 * It prevents weapons from being wielded while worn.
 */
mixed
wield(object wep)
{
    if (!knuckles)
        remove_knuckles_shadow();

    return "The palm bars of the brass knuckles you are wearing prevent you "
    + "from wielding or holding anything while they are worn.\n";
}

/* This is called when the wearer tries to wear armour
 * It prevents shields from being worn.
 */
mixed
wear_arm(object arm)
{
    if (!knuckles)
    {
        remove_knuckles_shadow();
    }

    if (arm->query_at() == A_SHIELD)
    {
        return "The brass knuckles you are wearing prevent "
        + "you from properly employing a shield while they are worn.\n";
    }

    return shadow_who->wear_arm(arm);
}
