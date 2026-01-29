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
    set_short("solid iron helm");
    set_adj(({"solid", "iron", }));
    set_long("This helmet appears to be very well made. With solid iron " +
        "on the outside and heavy padding on the inside, you would feel " +
        "quite confident using this helm in battle.\n");
    	        
    set_at(A_HEAD);
    set_ac(27);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 2500);
    
}
