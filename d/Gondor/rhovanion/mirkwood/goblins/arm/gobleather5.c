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
    set_short("studded leather armour");
    set_adj("studded");
    set_long("This is a suit of leather armour with several metal studs " +
        "embedded into the surface. It looks to be in very good condition, " +
        "and you guess it would serve you quite well in a fight.\n");
    	        
    set_at(A_BODY);
    set_ac(34);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3800);
    
}
