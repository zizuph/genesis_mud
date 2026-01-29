#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("robe");
    set_adj("velvet");
    add_adj("black");
    set_long("A luxurious robe made of some incredibly dark material.\n");
    set_ac(4);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 400);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,2500);
}
