/*
 * Shirt for Faelund
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
    set_short("brown shirt");
    set_long("This shirt appears to be covered in stains from a wide " +
        "variety of food and drink, but for all that, it still appears " +
        "to be in a wearable condition.\n");
    	    
    add_adj("brown");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
