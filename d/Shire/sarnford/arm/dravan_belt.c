/*
 * Shirt for Bill
 * Varian - February 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("belt");
    set_pname("belts");
    set_short("wide, cloth belt");
    set_long("This cloth belt looks like it would do a good job of keeping " +
        "loose clothing in place.\n");
    	    
    add_adj("wide");
    add_adj("cloth");
    
    set_at(A_WAIST);
    set_ac(1);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
