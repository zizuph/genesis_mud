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
    set_name(({"sledge","sledge hammer", "hammer"}));
    set_pname(({"hammers","sledges", "sledge hammers"}));
    set_short("heavy iron sledge");
    set_pshort("heavy iron sledges");
    set_adj(({"heavy", "iron"}));
    set_long("This is a long, heavy blacksmith's sledge hammer. The handle " +
        "has been carved from sturdy oak, and when combined with the blunt " +
        "iron head, the entire sledge becomes a very effective tool. You " +
        "would need to be very strong indeed to effectively use the sledge.\n");
    	    
    set_hit(10);
    set_pen(35);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(22,22));
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 2000);
    
}
