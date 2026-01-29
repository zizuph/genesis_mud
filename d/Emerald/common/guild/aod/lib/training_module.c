/*
 *  /d/Emerald/common/guild/aod/lib/training_module.c
 *
 *  This code controls the levels at which the army is able to train
 *  their skills higher. It can also be accessed by the master file.
 *
 *  Created February 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

#include <ss_types.h>


/*
 * Function name:        aod_training_check
 * Description  :        returns the level to which a person can train
 *                       in a given skill area.
 * Arguments    :        int  snum  - the skill we are checking for,
 *                       int  skulls - the number of skulls collected.
 * Returns      :        int - the level to which training may occur.
 */
public int
aod_training_check(int snum, int skulls)
{
    switch(snum)
    {
        case SS_PARRY:
            switch(skulls)
            {
                case 0..249:
                    return 0;
                    break;
                case 250..499:
                    return 40;
                    break;
                case 500..999:
                    return 50;
                    break;
                case 1000..1999:
                    return 60;
                    break;
                case 2000..2499:
                    return 65;
                    break;
                case 2500..2999:
                    return 66;
                    break;
                case 3000..3999:
                    return 67;
                    break;
                case 4000..4999:
                    return 68;
                    break;
                case 5000..5999:
                    return 69;
                    break;
                case 6000..6999:
                    return 70;
                    break;
                case 7000..7499:
                    return 71;
                    break;
                case 7500..7999:
                    return 72;
                    break;
                case 8000..8999:
                    return 73;
                    break;
                case 9000..9999:
                    return 74;
                    break;
                default:
                    return 75;
                    break;
            }
            break; /* case SS_PARRY: */
        case SS_WEP_CLUB:
            switch(skulls)
            {
                case 0..49:
                    return 0;
                    break;
                case 50..99:
                    return 50;
                    break;
                case 100..249:
                    return 55;
                    break;
                case 250..499:
                    return 65;
                    break;
                case 500..999:
                    return 75;
                    break;
                case 1000..1999:
                    return 85;
                    break;
                case 2000..2499:
                    return 86;
                    break;
                case 2500..2999:
                    return 87;
                    break;
                case 3000..3999:
                    return 88;
                    break;
                case 4000..4999:
                    return 89;
                    break;
                case 5000..5999:
                    return 90;
                    break;
                case 6000..6999:
                    return 91;
                    break;
                case 7000..7999:
                    return 92;
                    break;
                case 8000..8999:
                    return 93;
                    break;
                case 9000..9999:
                    return 94;
                    break;
                case 10000..14999:
                    return 95;
                    break;
                case 15000..24999:
                    return 96;
                    break;
                case 25000..34999:
                    return 97;
                    break;
                case 35000..49999:
                    return 98;
                    break;
                case 50000..74999:
                    return 99;
                    break;
                default:
                    return 100;
                    break;
            }
            break; /* case SS_WEP_CLUB: */
        case SS_2H_COMBAT:
            switch(skulls)
            {
                case 0..4999:
                    return 0;
                    break;
                case 5000..5999:
                    return 50;
                    break;
                case 6000..6999:
                    return 60;
                    break;
                case 7000..7999:
                    return 70;
                    break;
                case 8000..8999:
                    return 80;
                    break;
                case 9000..9999:
                    return 90;
                    break;
                case 10000..19999:
                    return 91;
                    break;
                case 20000..29999:
                    return 92;
                    break;
                case 30000..39999:
                    return 93;
                    break;
                case 40000..49999:
                    return 94;
                    break;
                case 50000..59999:
                    return 95;
                    break;
                case 60000..69999:
                    return 96;
                    break;
                case 70000..79999:
                    return 97;
                    break;
                case 80000..89999:
                    return 98;
                    break;
                case 90000..99999:
                    return 99;
                    break;
                default:
                    return 100;
                    break;
            }
            break; /* case SS_2H_COMBAT: */
        case SS_AOD_WALLOP:
            switch(skulls)
            {
                case 0..9:
                    return 0;
                    break;
                case 10..99:
                    return 50;
                    break;
                case 100..199:
                    return 60;
                    break;
                case 200..299:
                    return 65;
                    break;
                case 300..399:
                    return 70;
                    break;
                case 400..499:
                    return 75;
                    break;
                case 500..599:
                    return 80;
                    break;
                case 600..699:
                    return 85;
                    break;
                case 700..799:
                    return 90;
                    break;
                case 800..999:
                    return 91;
                    break;
                case 1000..1499:
                    return 92;
                    break;
                case 1500..1999:
                    return 93;
                    break;
                case 2000..2999:
                    return 94;
                    break;
                case 3000..3999:
                    return 95;
                    break;
                case 4000..4999:
                    return 96;
                    break;
                case 5000..5999:
                    return 97;
                    break;
                case 6000..6999:
                    return 98;
                    break;
                case 7000..7999:
                    return 99;
                    break;
                default:
                    return 100;
                    break;
            }
            break; /* case SS_AOD_WALLOP: */
        default:
            return 0;
            break;
    }
} /* aod_training_check */