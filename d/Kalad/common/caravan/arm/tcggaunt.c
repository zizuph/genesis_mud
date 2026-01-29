#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("gauntlets");
    set_adj("bronze");
    set_pshort("bronze gauntlets");
    set_long("Bronze plates that encircle and protect your arms from damage. Engraved upon it "+
      "is an image of a gold coin with lines radiating from it.\n");
    set_ac(18);
    set_am(({-5,-5,5}));
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);
}
