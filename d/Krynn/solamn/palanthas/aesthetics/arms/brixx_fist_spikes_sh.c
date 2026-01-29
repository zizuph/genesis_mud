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
 *
 * Ported over to use unarmed_enhancers.
 *
 * Ckrik 11.2021
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
