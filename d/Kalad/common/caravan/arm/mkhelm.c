#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("helm");
    set_adj("large");
    add_adj("thanar");
    set_long("A large, encovering helmet. Engraved upon the front is an "+
      "image of a dark sun.\n");
    set_ac(19);
    set_am(({0,-5,0}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_WEIGHT,2500);
}
