/*
 * Tunic for Sheriff
 * - Finwe, April 2002
 */
inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("tunic");
    set_pname("tunics");
    set_short("leather tunic");
    set_long("This is a plain tunic worn by many Breelanders. It " +
        "is simple in style.\n");
    	    
    set_adj("leather");
    
    set_at(A_BODY);
    set_ac(8);
    set_am(({ 4, 2, -6 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
