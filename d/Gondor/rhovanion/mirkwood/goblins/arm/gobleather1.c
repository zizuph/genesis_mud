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
    set_short("ragged leather armour");
    set_adj("ragged");
    set_long("This heavy suit of armour is made from leather, boiled " +
        "hard to give your body some protection. However, it has " +
        "obviously seen better days as it looks rather ragged.\n");
    	        
    set_at(A_BODY);
    set_ac(29);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 3800);
    
}
