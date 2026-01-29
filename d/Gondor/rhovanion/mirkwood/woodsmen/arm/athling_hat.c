/*
 * Hat for Athling
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
    set_short("fancy hat");
    set_long("This hat looks very fancy and stylish. The broad brim is " +
        "quite firm, and a large bird feather has been attached to the " +
        "left side to make a bit of a fashion statement.\n");
    	    
    add_adj("fancy");
    
    set_at(A_HEAD);
    set_ac(1);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 400);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 500);
    
}
