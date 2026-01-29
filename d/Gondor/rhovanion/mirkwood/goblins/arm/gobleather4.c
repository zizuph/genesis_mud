/*
 * Varian - Februart 5 2016
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
    set_short("dirty leather armour");
    set_adj("dirty");
    set_long("This is a rather dirty and smell piece of leather armour, " +
        "but it still looks like it could protect you in battle.\n");
    	        
    set_at(A_BODY);
    set_ac(30);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3800);
    
}
