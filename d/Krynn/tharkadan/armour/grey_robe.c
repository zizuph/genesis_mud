inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("robe");
    set_ac(20);
    set_at(A_ROBE);
    set_adj("grey");
    set_short("grey robe");
    set_long("This is a thick grey robe made from the silk of giant " +
       "spiders found in subterranean depths, providing warmth and " +
       "good protection.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_ROBE));
}


