/*
 * Shirt for Laone
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
    set_short("rough shirt");
    set_long("This shirt is made from a rather rough and coarse fabric. It " +
        "would not be the most comfortable thing to wear, but you suspect " +
        "it would be quite practical to wear in a dense forest.\n");
    	    
    add_adj("rough");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
