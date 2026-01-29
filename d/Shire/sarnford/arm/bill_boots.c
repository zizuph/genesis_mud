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
    set_name("pair of boots");
    set_pname("pairs of boots");
    set_short("sturdy, leather pair of boots");
    set_long("These leather boots look a little waterstained, but are otherwise " +
        "quite sturdy looking.\n");
    	    
    add_adj("sturdy");
    add_adj("leather");
    
    set_at(A_FEET);
    set_ac(5);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
