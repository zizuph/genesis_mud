/* Stralle @ Genesis 030824
 */

#pragma strict_types

inherit "/std/shadow";

#include <stdproperties.h>
#include <formulas.h>

int fatigue_time = time();

/* Function name: calculate_fatigue
 * Description:   Gets called whenever fatigue is added to the player
 *                By redefining this in this shadow and calling the
 *                original function, basically what is done is adding
 *                fatigue twice to the player whenever he is supposed
 *                to heal fatigue. Here the formula is slightly changed
 *                so that this function will only increase fatigue every
 *                F_INTERVAL_BETWEEN_FATIGUE_HEALING * 3 / 2 seconds
 *                which will make it 50% longer. The two adding up
 *                will effect in 50% increase in fatigue healing rate.
 */
void
calculate_fatigue()
{
    int n;
    
    n = (time() - fatigue_time) / ((F_INTERVAL_BETWEEN_FATIGUE_HEALING * 3) / 2);
    if (n > 0)
    {
        fatigue_time += n * ((F_INTERVAL_BETWEEN_FATIGUE_HEALING * 3) / 2);
        query_shadow_who()->add_fatigue(n *
            F_FATIGUE_FORMULA(query_shadow_who()->query_stuffed(),
                query_shadow_who()->query_prop(LIVE_I_MAX_EAT)));
    }

    query_shadow_who()->calculate_fatigue();
}

void
remove_boots_shadow()
{
    remove_shadow();
}
