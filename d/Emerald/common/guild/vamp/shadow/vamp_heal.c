/* vamp_heal.c created by Shiva@Genesis.
 * This file contains code related to a vampire's healing rates
 * This is part of the vampire guild shadow
 */

#include "../guild.h"
#include <formulas.h>

#define SW shadow_who

static private int last_heal_hp;   // Last time I updated my hitpoints
static private int last_vstat;     // Occ stat at last hp update
static private int last_blood;     // Blood thirst at last hp update
static private int last_heal_ftg;  // Last time I updated my fatigue
static private int last_vstat_ftg; // Occ stat at last fatigue update
static private int last_blood_ftg; // Thirst at last fatigue update

/*
 * Function name: start_heal
 * Description:   initialize vampire healing variables
 */
static void start_heal()
{
#ifndef NO_HEAL
    last_heal_ftg = last_heal_hp = time();
    last_vstat_ftg = last_vstat = query_vamp_stat();
    last_blood = MAX(0, query_max_thirst() - query_thirst());
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
    int n, vstat, tmpvstat, blood, tmpblood, heal;

    SW->calculate_hp();
      
    if (F_INTERVAL_BETWEEN_HP_HEALING)
    {
        n = (time() - last_heal_hp) / F_INTERVAL_BETWEEN_HP_HEALING;
    
        if (n > 0)
        {
            vstat = query_vamp_stat();
            blood = MAX(0, query_max_thirst() - query_thirst());
            tmpvstat = (vstat + last_vstat) / 2;
            tmpblood = (blood + last_blood) / 2;
      
            last_vstat = vstat;
            last_blood = blood;
            last_heal_hp += n * F_INTERVAL_BETWEEN_HP_HEALING;
      
            switch (thirst())
            {
                case 90..100:
                    /* A vampire with thirst in excess of 89% heals more
                     * slowly than a non-vamp.  Heal a negative value here
                     * to account for that.
                     */
          
                    heal = MIN(-5, -query_thirst() * n / 10);
          
                    SW->heal_hp(heal);
                    break;
        
                case 0..49:
                    /* Accelerated healing if thirst is < 50% */
          
                    heal = F_HEAL_FORMULA(tmpblood / 2, tmpvstat);
                    heal *= n;
          
                    SW->heal_hp(heal);
                    break;
            }
        }
    }  

}
#endif

#ifndef NO_HEAL_FATIGUE
/* 
 * Function name: calculate_fatigue
 * Description:   calculate the amount of fatigue that has
 *                been healed since last time checked and add 
 *                it to the player.
 */
void calculate_fatigue()
{
    int n, blood, tmpblood, fatigue;

    SW->calculate_fatigue();
      
    if (F_INTERVAL_BETWEEN_FATIGUE_HEALING)
    {
        n = (time() - last_heal_ftg) / F_INTERVAL_BETWEEN_FATIGUE_HEALING;
    
        if (n > 0)
        {
            blood = MAX(0, query_max_thirst() - query_thirst());
            tmpblood = (blood + last_blood_ftg) / 2;
      
            last_blood_ftg = blood;
            last_heal_ftg += n * F_INTERVAL_BETWEEN_FATIGUE_HEALING;
      
            switch (thirst())
            {
                case 90..100:
                    /* A vampire with thirst in excess of 89% heals more
                     * slowly than a non-vamp.  Heal a negative value here
                     * to account for that.
                     */
          
                    fatigue = MIN(-2, -query_thirst() * n / 20);
          
                    SW->add_fatigue(fatigue);
                    break;
        
                case 0..80:
                    /* Accelerated healing if thirst is <= 80% */
          
                    fatigue = F_FATIGUE_FORMULA(tmpblood * 2, 
                        query_max_thirst());
                    fatigue *= n;
          
                    SW->add_fatigue(fatigue);
                    break;
            }
        }
    }
}
#endif


