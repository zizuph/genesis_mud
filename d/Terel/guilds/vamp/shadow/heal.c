/* vamp_heal.c created by Shiva@Genesis.
 * This file contains code related to a vampire's healing rates
 * This is part of the vampire guild shadow
 */

#include "../guild.h"
#include "../defs.h"
#include <formulas.h>

#define SW shadow_who

static private int last_thirst_heal;    // Thirst at last updated heal
static private int last_thirst_ftg;     // Thirst at last updated fatigue

private int recursive_lock      = 0;

/*
 * Function name: start_heal
 * Description:   initialize vampire healing variables
 */
static void start_heal()
{
#ifndef NO_HEAL
    last_thirst_heal = thirst();
    last_thirst_ftg = thirst();
    send_debug_message("vamp_shadow", "Vampire healing started.");
#endif
}


#ifndef NO_HEAL
/* 
 * Function name: calculate_hp()
 * Description:   calculate the number of hitpoints that
 *                have been healed since last time checked
 *                and add them to the player.
 */
void calculate_hp()
{
    int n, tmpthirst;
    
    if (recursive_lock)
    {
        return;
    }
    
    recursive_lock = 1;
    
    int oldhp, newhp, normal_heal, vamp_heal, intox;
    oldhp = SW->query_hp();
    SW->calculate_hp();
    newhp = SW->query_hp();
    
    if (oldhp < newhp)
    {
        normal_heal = newhp - oldhp;
        send_debug_message("vamp_shadow", "Vampire normal healed for "
            + normal_heal + " hit points.");
        
        n = normal_heal / F_HEAL_FORMULA(SW->query_stat(SS_CON), 0);
    }
    
    if (n > 0)
    {
        /* Vampire Regeneration was not acting according to
         * documented values.
         * Changed February 2009.
         * Vamp regeneration is dependent on blood level. At 90%
         * thirst, a vamp heals the same as a normal mortal.
         * More thirst than that and they actually heal slower.
         * Less thirst, they can get up to the full intox value
         * of normal mortals.
         */

        // Use tmpthirst to get an average over the period of time
        tmpthirst = (thirst() + last_thirst_heal) / 2;    
        intox = SW->intoxicated_max();
        // Multiply the max intox by a factor of their thirst
        switch (tmpthirst)
        {
        case 90..100:
            intox = intox * (90 - tmpthirst) / 10;
            break;
        
        default:
            intox = intox * (90 - tmpthirst) / 90;
            break;
        }
        // Get how much the vamp should be healing. This should be
        // a positive value if their thirst is less than half.
        vamp_heal = F_HEAL_FORMULA(QSW->query_stat(SS_CON), intox);
        vamp_heal *= n;
        vamp_heal -= normal_heal;
        SW->heal_hp(vamp_heal);                 
        send_debug_message("vamp_shadow", "Vampire heals for "
            + vamp_heal + " hit points based on " + tmpthirst
            + "% thirst.");
        
        last_thirst_heal = thirst();
    }
    
    recursive_lock = 0;
}
#endif

/* 
 * Function name: calculate_fatigue
 * Description:   calculate the amount of fatigue that has
 *                been healed since last time checked and add 
 *                it to the player.
 */
void calculate_fatigue()
{
    int n, tmpthirst;

    if (recursive_lock)
    {
        return;
    }
    
    recursive_lock = 1;
    
    int oldftg, newftg, normal_ftg, vamp_ftg, stuffed;
    oldftg = SW->query_fatigue();
    SW->calculate_fatigue();
    newftg = SW->query_fatigue();
    
    if (oldftg < newftg)
    {
        normal_ftg = newftg - oldftg;
        n = normal_ftg / F_FATIGUE_FORMULA(0, SW->query_prop(LIVE_I_MAX_EAT));
        send_debug_message("vamp_shadow", "Vampire gained fatigue of "
            + normal_ftg + " points over " + n + " intervals.");        
    }

    if (n > 0)
    {
        /* Vampire Fatigue Regen was not acting according to
         * documented values.
         * Changed February 2009.
         * Fatigue regen egeneration is dependent on blood level. At 90%
         * thirst, a vamp has same level as a normal mortal.
         * More thirst than that and they actually regain slower.
         * Less thirst, they can get up to the twice full stuffed value
         * of normal mortals.
         */
        // Use tmpthirst to get an average over the period of time
        tmpthirst = (thirst() + last_thirst_ftg) / 2;             
        stuffed = SW->query_prop(LIVE_I_MAX_EAT);
        // Multiply the max stuffed by a factor of their thirst
        switch (tmpthirst)
        {
        case 90..100:
            vamp_ftg = normal_ftg * (90 - tmpthirst) / 10;
            break;
        
        default:
            stuffed = stuffed * (90 - tmpthirst) / 90;
            vamp_ftg = F_FATIGUE_FORMULA(stuffed, 
                SW->query_prop(LIVE_I_MAX_EAT));
            // Vampires can get fatigue back at double the rate
            vamp_ftg *= 2;
            vamp_ftg *= n;
            vamp_ftg -= normal_ftg;
            break;
        }
        
        SW->add_fatigue(vamp_ftg);                 
        send_debug_message("vamp_shadow", "Vampire adds "
            + vamp_ftg + " fatigue points based on " + tmpthirst
            + "% thirst over " + n + " intervals.");        
        
        last_thirst_ftg = thirst();
    }

    recursive_lock = 0;
}


