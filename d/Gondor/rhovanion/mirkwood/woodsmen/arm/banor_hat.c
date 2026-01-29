/*
 * Hat for Banor
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
    set_name("hat");
    set_short("soft hat");
    set_long("This soft hat looks rather comfortable, and rather fashionable " +
        "now that you examine it a little closer.\n");
    	    
    add_adj("soft");
    
    set_at(A_HEAD);
    set_ac(1);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 500);
    
}
