
/* 
    The commander kroug's polearm of darkness. 

    coder(s):   Glykron and Maniac 
    history: 
    27/1/2000    adapted from sword, inherits from new  
                 "weapon of opposites"                        Maniac 
         2/99    burns out after approx 7 hours               Maniac 
     12/12/98    added darkness removal                       Maniac 
      3/12/98    added logging                                Maniac 
       6/6/96    made keepable                                Maniac 
       6/4/96    some properties added                        Maniac 
      18/8/95    wieldable in any hand                        Maniac 
     24. 2.93    recovery added                               Glykron 
      9. 2.93    header added                                 Glykron 
*/ 

#pragma save_binary 

#include "defs.h" 
inherit (CRPALACE_WEAPONS + "weapon_of_opposites"); 
inherit "/lib/keep"; 
#include <wa_types.h> 
#include <formulas.h> 
#include <stdproperties.h> 
#include <macros.h> 



void 
create_weapon() 
{ 
    if (query_woo_name() == 0) { 
        switch (random(5)) { 
            case 0 : 
                set_woo_name("halberd"); 
                set_plural_woo_name("halberds"); 
                break; 
            case 1 : 
                set_woo_name("lance"); 
                set_plural_woo_name("lances"); 
                break; 
            default : // spears are intentionally more likely than others 
                set_woo_name("spear"); 
                set_plural_woo_name("spears"); 
                break; 
        } 
    } 
    set_transformation_state(0, 0, 0); 
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, "evil"); 
} 



/* 
 * Function:     config_transformation_stats 
 * Description:  Makes the appropriate changes to the weapon 
 *               stats when a transformation occurs. 
 */ 
void 
config_transformation_stats(int new_state) 
{ 
    if (new_state == 0 || 
        new_state == 1) { 
        set_hit(40); 
        set_pen(40); 
        set_hands(W_ANYH); 
        set_wt(W_POLEARM); 
        set_dt(W_IMPALE); 
    } 
} 
