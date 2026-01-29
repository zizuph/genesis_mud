/*
 * Pants for Banor
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
    set_name("pants");
    set_pshort("pairs of pants");
    add_name("pair of pants");
    set_short("white pair of pants");
    set_pshort("white pairs of pants");
    set_long("You would normally expect a white pair of pants to get dirty " +
        "fairly quickly, but apparently the previous owner took rather good " +
        "care of his clothing.\n");
    	    
    add_adj("white");
    
    set_at(A_LEGS);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
