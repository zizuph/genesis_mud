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
    set_name("hat");
    set_pname("hats");
    set_short("wide-brimmed, straw hat");
    set_long("This straw hat has a very wide brim, it would give you excellent " +
        "protection from the sun.\n");
    	    
    add_adj("wide-brimmed");
    add_adj("straw");
    
    set_at(A_HEAD);
    set_ac(5);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
