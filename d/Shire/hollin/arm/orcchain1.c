/*
 * Varian - Februart 5 2016
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("helm");
    add_name("helmet");
    set_short("brown leather helm");
    set_adj(({"brown", "leather", }));
    set_long("This is a rather simple leather helmet, reinforced with " +
        "some iron bands to provide a little extra protection.\n");
    	        
    set_at(A_HEAD);
    set_ac(24);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 1200);
    
}
