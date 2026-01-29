/*
 * Varian - October 5 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("leather armour");
    add_name("leather");
    set_short("grey leather armour");
    set_adj("grey");
    set_long("This leather armour has greyed with age, but it still seems " +
        "to be in a servicable condition.\n");
    	        
    set_at(A_BODY);
    set_ac(28);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
