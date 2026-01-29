/* 
 * Inherit for attitudes of npcs in Gelan. 
 * Calians, graduates and cadets are assumed to know 
 * these npcs as long as they've done the town tour! 
 * 
 * Coded by Maniac, 4/3/01. 
 */ 

inherit "/d/Calia/std/attitude";

#include "specials.h" 
#include "/d/Calia/gelan/cadet/cadet.h"


/* 
 * Function:       query_knows_me 
 * Description:    Returns 1 if the living should know this npc 
 *                 0 otherwise (the default). 
 * 
 */ 
int 
query_knows_me(object living) 
{ 
    int tmp; 

    if ((tmp = living->query_prop(LIVE_I_KNOW_CALIA_GELAN_NPCS)) == 1) 
        return 1; 
    else if (tmp == -1) 
        return 0; 

    if (living->test_bit("Calia", 1, 4) && 
        (living->is_calian_warrior() || 
         IS_GRADUATE(living) || 
         IS_GELAN_CADET(living))) { 
        living->add_prop(LIVE_I_KNOW_CALIA_GELAN_NPCS, 1); 
        return 1; 
    } 
    living->add_prop(LIVE_I_KNOW_CALIA_GELAN_NPCS, -1); 
    return 0; 
} 
