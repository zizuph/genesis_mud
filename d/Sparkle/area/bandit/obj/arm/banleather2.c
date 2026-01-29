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
    set_short("studded leather armour");
    set_adj("studded");
    set_long("This suit of leather armour has metal studs embedded into " +
        "the body for extra protection. Under reasonable conditions, " +
        "you think this armour should serve you well in combat.\n");
    	        
    set_at(A_BODY);
    set_ac(32);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
