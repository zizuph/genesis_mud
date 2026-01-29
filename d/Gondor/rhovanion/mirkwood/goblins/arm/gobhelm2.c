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
    set_short("worn leather helm");
    set_adj(({"worn", "leather", }));
    set_long("This helmet is made from a soft leather, worn down from " +
        "years of use. Some iron bands reinforce the helm for extra " +
        "protection, but this is quite clearly the equipment of a " +
        "warrior who was somewhat short on funds.\n");
    	        
    set_at(A_HEAD);
    set_ac(23);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 1200);
    
}
