/*
 * Varian - February 5 2016
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("shield");
    set_short("rough leather shield");
    set_adj(({"rough", "leather", }));
    set_long("This shield has a wooden frame with a rough piece of leather " +
        "stretched across the surface. It might not be the most elegant " +
        "piece of armour, but it is light and reasonably effective.\n");
    	        
    set_at(A_SHIELD);
    set_ac(27);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
