/* Roast venison, which can be purchased (its rather expensive) from
   the bandits at /thief_lair/cave9.
   Code (c) 1999 to Damian Horton (BKA Casimir)
*/

inherit "/std/food";

#include <stdproperties.h>

create_food()
{
    set_name("venison");
    add_name("skewer");
    set_adj("roast");
    set_short("skewer of roast venison");
    set_long("A hunk of deer meat, skewered on a short wooden stake and "+
	     "roasted over an open fire. It is nice and juicy.\n");

    set_amount(500); 
    add_prop(OBJ_I_WEIGHT, 600);  
    add_prop(OBJ_I_VOLUME, 700);
}





