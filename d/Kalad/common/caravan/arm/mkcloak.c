#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("cloak");
    set_adj("thick");
    add_adj("velvet-black");
    set_long("A long, thickly-lined cloth cape. Upon it is engraved an "+
      "image of a dark sun.\n");
    set_ac(4);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
}
