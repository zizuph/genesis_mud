/*
 * Smiths hammer
 * Varian - April 2015
 */

inherit "/std/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


create_weapon()
{
    int rand;
    
    set_name(({"sledge","sledge hammer", "hammer"}));
    set_pname(({"hammers","sledges", "sledge hammers"}));
    set_short("black sledge");
    set_pshort("black sledges");
    set_adj(({"black"}));
    set_long("This is a long, heavy blacksmith's sledge hammer. The handle " +
        "has been carved from a black wood, and when combined with the dark " +
        "iron head, the entire sledge looks like one large black tool. You " +
        "would need to be very strong indeed to effectively use the sledge.\n");
    	    
    rand = random(5);
    set_hit(10);
    set_pen(35);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(22,22));
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 2000);
    
}
