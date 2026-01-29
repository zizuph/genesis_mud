/*
    These are functions that are used many places in various College
    spells and spell objects, to avoid duplication.

    Bishop of Calia, July 2003.

 */

#include <ss_types.h>
#include "defs.h"


/*
    This function computes and returns the controlling stat, that is, 
    the stat we use when computing how well a spell with variable
    effects performs. The inputs are the element of the caster and
    an objectpointer to him/her.
*/
int
find_controlling_stat(string str, object pl)
{
    int stat;
    
    switch (str)
    {
        case "fire":
            stat = (pl->query_stat(SS_INT)* 40 + 
                pl->query_stat(SS_WIS)* 10 + 
                pl->query_stat(SS_DIS)* 50) / 100;
            break;
        case "air":
            stat = (pl->query_stat(SS_INT)* 40 + 
                pl->query_stat(SS_WIS)* 20 + 
                pl->query_stat(SS_DIS)* 40) / 100;
            break;
        case "water":
            stat = (pl->query_stat(SS_INT)* 50 + 
                pl->query_stat(SS_WIS)* 30 + 
                pl->query_stat(SS_DIS)* 20) / 100;
            break;
        case "earth":
            stat = (pl->query_stat(SS_INT)* 40 + 
                pl->query_stat(SS_WIS)* 40 + 
                pl->query_stat(SS_DIS)* 20) / 100;
            break;
        default:
            stat = 0;
    }
    
    stat = min(stat, pl->query_stat(SS_OCCUP));
    
    if (pl->query_skill(SS_COLLEGE_BITS) & APPRENTICE_LVL_BIT)
    {
        stat = max(0, stat-50);
    }
    else 
    if (pl->query_skill(SS_COLLEGE_BITS) & SCHOLAR_LVL_BIT)
    {
       stat += 50;
    }

    if (pl->query_wiz_level())
    {
        stat = 120;
    }
    
    return stat;
}                        