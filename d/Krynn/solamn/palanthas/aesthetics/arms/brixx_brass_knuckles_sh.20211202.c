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

/* Called from the combat sys when we make an attack */
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
  int dt, int phit, int dam)
{
    if (!knuckles)
    {
        remove_shadow();
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    /* If the unarmed attack has done more than 25 hps damage and the
     * attack is done with the right or left hand, we call a function
     * in the knuckles to do special damage.  Returning 1 disables the
     * combat system's normal handling of the remainder of the unarmed
     * attack; the special_damage() function in the knuckles takes care
     * of combat messages, etc.
     */
    if ((phurt >= 0) && (dam > 25) && (aid && W_BOTH) && 
        knuckles->special_damage(aid, hdesc, phurt, enemy, phit, dam))
    {
        return 1;
    }

    return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

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
