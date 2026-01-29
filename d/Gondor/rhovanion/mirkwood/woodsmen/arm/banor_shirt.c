/*
 * Shirt for Banor
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
    set_short("red shirt");
    set_long("This shirt has been made from wool dyed a very bright red! " +
        "It looks rather warm, but it would probably not be very good to " +
        "wear while playing 'hide and seek'.\n");
    	    
    add_adj("red");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
