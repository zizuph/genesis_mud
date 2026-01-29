/* 
 * Shadow of fist spikes used by ranking Brix gangers behind
 * Jems court in the Aesthetics quarter of Palanthas.
 *
 * Based on the coding concept behind Shiva's flaming spikes
 * found on Lyden in Tyr.
 *
 * It detects wielding/unwielding of weapons and unarmed attacks,
 * calling the appropriate functions in the spikes.
 *
 * Mortis 06.2006
 *
 * Allowed weapons to be used but not shields. Mortis 9.2014
 *
 * These have been reviewed by AoB and returned to blocking weapons
 * due to thematic discrepancies, the spikes affected the damage of
 * bludgeon weapons.
 *
 * Carnak 02.2016
 */

#include <wa_types.h>

inherit "/std/shadow";

static object spikes;

void
remove_spikes_shadow()
{
    remove_shadow();
}

int
query_spikes_shadow() {return 1;}

void
set_spikes_ob(object ob) {spikes = ob;}

object
query_spikes_ob() {return spikes;}

/* Called from the combat sys when we make an attack */
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
  int dt, int phit, int dam)
{
    if (!spikes)
    {
        remove_shadow();
        return shadow_who->cr_did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    /* If the unarmed attack has done more than 25 hps damage and the
     * attack is done with the right or left hand, we call a function
     * in the spikes to do special damage.  Returning 1 disables the
     * combat system's normal handling of the remainder of the unarmed
     * attack; the special_damage() function in the spikes takes care
     * of combat messages, etc.
     */
    if ((phurt >= 0) && (dam > 20) && (aid & W_BOTH) && 
        spikes->special_damage(aid, hdesc, phurt, enemy, phit, dam))
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
    if (!spikes)
        remove_spikes_shadow();

    return "The palm bars of the fist spikes you are wearing prevent you "
    + "from wielding or holding anything while they are worn.\n";
}

/* This is called when the wearer tries to wear armour
 * It prevents shields from being worn.
 */
mixed
wear_arm(object arm)
{
    if (!spikes)
    {
        remove_spikes_shadow();
    }

    if (arm->query_at() == A_SHIELD)
    {
        return "The fist spikes you are wearing prevent "
        + "you from properly employing a shield while they are worn.\n";
    }

    return shadow_who->wear_arm(arm);
}
