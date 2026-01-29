#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("greaves");
    set_adj("bronze");
    set_pshort("bronze greaves");
    set_long("A pair of leg armours made entirely of bronze. On each "+
      "is an image of a gold coin with lines radiating from it.\n");
    set_ac(20);
    set_am(({-5,-5,5}));
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,4000);
}
