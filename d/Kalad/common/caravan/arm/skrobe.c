#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("robe");
    set_adj("midnight");
    add_adj("black");
    set_long("This luxurious robe is made of some velvety black substance. "+
      "Peering closer at it you notice a distorted image of yourself looking "+
      "back.\n");
    set_ac(3);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,2000);
}
