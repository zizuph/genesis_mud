/*
 * Gruk's pants
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
    set_name("loincloth");
    set_short("plain white loincloth");
    set_long("This is a plain, white loincloth. It smells a little funny, " +
        "but otherwise it seems wearable.\n");
    	    
    add_adj("plain");
    add_adj("white");
    
    set_at(A_LEGS);
    set_ac(10);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
