
/* 
    The commander kroug's sword of darkness. 

    coder(s):   Glykron and Maniac 
    history: 
    27/1/2000    inherits from new "weapon of opposites"      Maniac 
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
    set_woo_name("sword"); 
    set_plural_woo_name("swords"); 
    set_transformation_state(0, 0, 0); 
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, "evil"); 
}
