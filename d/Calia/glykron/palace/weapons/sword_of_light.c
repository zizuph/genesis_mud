
/* 	
    The sword of light wielded by the white Calian in the crystalline 
    palace

    coder(s):   Glykron and Maniac
    history:    
    27/1/2000   inherits from new "weapon of opposites"     Maniac 
    23/2/99     light can burn out                          Maniac
    6/6/96      made keepable                               Maniac
    6/4/96      properties added                            Maniac
    18/8/95     made wieldable in any hand                  Maniac
    24. 2.93    recovery added                              Glykron
    9. 2.93     header added                                Glykron
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
    set_transformation_state(1, 0, 0); 
    add_prop(OBJ_S_ORIGIN_ALIGNMENT, "good"); 
} 
