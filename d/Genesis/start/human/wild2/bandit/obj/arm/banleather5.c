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
    set_short("brown leather armour");
    set_adj("brown");
    set_long("This appears to be a fairly simple piece of armour. It is " +
        "made from some brown leather, boiled until it has become stiff " +
        "and hard, able to provide some protection in battle.\n");
    	        
    set_at(A_BODY);
    set_ac(29);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1200);
    
}
