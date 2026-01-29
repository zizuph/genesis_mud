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
    set_name("helm");
    add_name("helmet");
    set_short("silvery steel helm");
    set_adj(({"silvery", "steel", }));
    set_long("The brightly polished steel of this helm shines brightly. " +
        "It appears to be well crafted, a fitting piece of armour for " +
        "a brave warrior.\n");
    	        
    set_at(A_HEAD);
    set_ac(29);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 2500);
    
}
