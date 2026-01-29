/*
 * Shirt for Athling
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
    set_name("shirt");
    set_short("white shirt");
    set_long("This shirt appears to be of a very fine quality! It is very " +
        "clean and the previous owner obviously took fine care of it.\n");
    	    
    add_adj("white");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 400);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
