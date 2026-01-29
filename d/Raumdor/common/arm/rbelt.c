/* dirty black belt, by Sarr */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("belt");
    set_adj("dirty");
    add_adj("black");
    set_short("dirty black belt");
    set_long("This belt is made out of black leather. On the buckle, "+
	     "you see etched, a golden sun with rays.\n");
    set_ac(5);
    set_at(A_WAIST);
    add_prop(OBJ_I_WEIGHT,460);
    add_prop(OBJ_I_VOLUME,360);
    add_prop(OBJ_I_VALUE,15);
}
