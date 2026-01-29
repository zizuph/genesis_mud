/*
 * Shirt for Bill
 * Varian - February 2015
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
    set_pname("hats");
    set_short("floppy, leather hat");
    set_long("This floppy leather hat would be perfect to wear while fishing!\n");
    	    
    add_adj("floppy");
    add_adj("leather");
    
    set_at(A_HEAD);
    set_ac(5);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
