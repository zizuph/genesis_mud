#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("shield");
    set_adj("large");
    add_adj("steel");
    set_long("This is a large shield, measuring three feet at its widest "+
      "point. A golden camel visible on the front marks this shield as "+
      "property of the captain of the city guard.\n");
    set_ac(21);
    set_at(A_SHIELD);
    add_prop(OBJ_I_VALUE, 480);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,2000);
}
