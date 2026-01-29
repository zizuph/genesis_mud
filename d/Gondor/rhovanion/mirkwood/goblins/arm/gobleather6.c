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
    set_short("painted leather armour");
    set_adj("painted");
    set_long("This suit of leather armour has been painted and decorated " +
        "with a wide variety of grim images and symbols. The most prominent " +
        "of which is a massive wolfhead, howling and covered in flames.\n");
    	        
    set_at(A_BODY);
    set_ac(35);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3800);
    
}
