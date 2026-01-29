#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("gauntlets");
    set_adj("light");
    add_adj("steel");
    set_short("light steel gauntlets");
    set_pshort("light steel gauntlets");
    set_long("A light pair of steel gauntlets, engraved upon them is an "+
      "image of a golden lion.\n");
    set_ac(12);
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,2500);
}
