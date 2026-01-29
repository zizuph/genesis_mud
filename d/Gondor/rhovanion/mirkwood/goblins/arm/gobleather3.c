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
    set_short("boiled leather armour");
    set_adj("boiled");
    set_long("This armour is essentially made from some large slabs of " +
        "leather which have been boiled hard to give you some protection " +
        "in battle. The armour has a funny smell, but it certainly " +
        "looks servicable.\n");
    	        
    set_at(A_BODY);
    set_ac(32);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3800);
    
}
