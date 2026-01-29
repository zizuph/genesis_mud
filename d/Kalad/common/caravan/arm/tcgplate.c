#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("platemail");
    set_adj("bronze");
    set_long("A suit of plate armour made entirely of bronze. On the "+
      "breastplate an image of a gold coin with lines radiating from it has "+
      "been engraved.\n");
    set_ac(32);
    set_am(({-5,-5,5}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 400);
    add_prop(OBJ_I_VOLUME,10000);
    add_prop(OBJ_I_WEIGHT, 15000);
}
