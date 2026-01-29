#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("gauntlets");
    set_adj("thanar");
    set_long("An extremely fine set of hand armours. Engraved upon each "+
      "gauntlet is an image of a dark sun.\n");
    set_ac(15);
    set_am(({0,-5,0}));
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_WEIGHT,5000);
}
