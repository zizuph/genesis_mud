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
    set_short("soft, leather belt");
    set_long("This leather belt is quite comfortable as the leather is remarkably soft. " +
        "It also adds a fashionable touch to your attire.\n");
    	    
    add_adj("soft");
    add_adj("leather");
    
    set_at(A_WAIST);
    set_ac(1);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
