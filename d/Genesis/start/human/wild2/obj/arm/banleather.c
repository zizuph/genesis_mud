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
    set_short("worn leather armour");
    set_adj("worn");
    set_long("This suit of leather armour is ragged and worn, but it " +
        "should still be able to offer you a little bit of protection.\n");
    	        
    set_at(A_BODY);
    set_ac(25);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
