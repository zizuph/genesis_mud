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
    set_short("round wooden shield");
    set_adj(({"round", "wooden", }));
    set_long("This large shield is perfectly round, if you ignore the chips " +
        "in the side of the wood that is.\n");
    	        
    set_at(A_SHIELD);
    set_ac(33);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 3000);
    
}
