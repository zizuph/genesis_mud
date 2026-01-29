/* this is the include file for the guards in Gelan

    history:
             26/7/95    Old file revised           Maniac
         
*/

/* ranks of the guards */

#define ENTRANCE_GUARD      0
#define RECRUIT_ENTRANCE_1  1
#define FIGHTER_ENTRANCE_1  2
#define EXP_ENTRANCE_1      3
#define GUIDE               4

#define MAX_RANKS 5

/* functions */

#define RESET_GUARD(rank)  (GELAN_SPECIALS + "head_guard")->search_free_guard(rank)

