#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("greaves");
    set_adj("thanar");
    set_long("A strong pair of leg armours. Engraved upon each is an image "+
      "of a dark sun.\n");
    set_ac(14);
    set_am(({0,-3,0}));
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_VOLUME,7500);
    add_prop(OBJ_I_WEIGHT,7500);
}
