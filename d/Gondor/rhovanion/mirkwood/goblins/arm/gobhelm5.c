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
    set_short("dented steel helm");
    set_adj(({"dented", "steel", }));
    set_long("This steel helm has seen better days. It is heavily dented " +
        "and battered, but you suppose it might still protect your head " +
        "a little bit.\n");
    	        
    set_at(A_HEAD);
    set_ac(26);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 2500);
    
}
