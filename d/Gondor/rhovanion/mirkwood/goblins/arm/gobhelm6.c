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
    set_short("black iron helm");
    set_adj(({"iron", "black", }));
    set_long("This is a rather simple iron helm. But then, it probably " +
        "doesn't need to be fancy, just effective.\n");
    	        
    set_at(A_HEAD);
    set_ac(25);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 2500);
    
}
