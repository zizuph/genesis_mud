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
    set_short("hard leather armour");
    set_adj("hard");
    set_long("This suit of leather armour is a bit heavy, having been boiled " +
        "hard to give better protection in battle. You would feel a little " +
        "more secure wearing something like this.\n");
    	        
    set_at(A_BODY);
    set_ac(31);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1200);
    
}
