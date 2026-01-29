/*
 * Varian - February 5 2016
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("shield");
    set_short("solid wooden shield");
    set_adj(({"solid", "wooden", }));
    set_long("This wooden shield is in very good condition, made from " +
        "solid wood, and banded in hard black iron.\n");
    	        
    set_at(A_SHIELD);
    set_ac(35);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, 3000);
    
}
