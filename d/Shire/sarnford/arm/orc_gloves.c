/*
 * Orc mail - Sarn Ford
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
    set_name("gloves");
    set_pname("gloves");
    set_short("thick, leather gloves");
    set_long("These gloves are made from a tough, thick leather which might " +
        "help to protect your hands. They look a little cracked and worn " +
        "with age, but they should still be servicable.\n");
    	    
    add_adj("thick");
    add_adj("leather");
    
    set_at(A_HANDS);
    set_ac(1);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
    
}
