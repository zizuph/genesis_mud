#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("helmet");
    set_adj("bronze");
    set_long("An enclosing piece of head armour made of bronze. On the "+
      "front an image of a gold coin with lines radiating from it has "+
      "been engraved.\n");
    set_ac(19);
    set_am(({-5,-5,5}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,3000);
}
