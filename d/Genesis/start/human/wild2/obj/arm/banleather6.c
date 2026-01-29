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
    set_short("creased leather armour");
    set_adj("creased");
    set_long("This suits of leather armour has become a bit bent and creased " +
        "with age, but it certainly still appears to be servicable.\n");
    	        
    set_at(A_BODY);
    set_ac(27);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1200);
    
}
