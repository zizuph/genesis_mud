/*
 * Blacksmith Apron
 * Varian - April 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("apron");
    set_pname("aprons");
    set_short("heavy apron");
    set_long("This is a heavy blacksmith's apron, it is designed to " +
        "protect the front of your body while working at the forge. It " +
        "is probably not much use if you are not planning on doing " +
        "any blacksmithing work.\n");
    	    
    add_adj("heavy");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 9000);
    
}
