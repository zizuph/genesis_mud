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
    set_name("pair of pants");
    set_pname("pairs of pants");
    set_short("worn, leather pair of pants");
    set_long("These pants are fairly sturdy, but have a distinct fishy smell to them.\n");
    	    
    add_adj("worn");
    add_adj("leather");
    
    set_at(A_LEGS);
    set_ac(10);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
