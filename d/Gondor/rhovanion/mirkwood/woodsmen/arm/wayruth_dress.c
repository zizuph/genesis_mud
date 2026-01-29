/*
 * Dress for Wayruth
 * Varian - August 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("dress");
    set_pname("dresses");
    set_short("brown dress");
    set_long("This is a very plain, yet still quite servicable, dress that " +
        "you can wear over your body.\n");
    	    
    add_adj("brown");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 9000);
    
}
