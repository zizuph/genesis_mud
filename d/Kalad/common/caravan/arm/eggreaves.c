#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("greaves");
    set_adj("light");
    add_adj("steel");
    set_short("light steel greaves");
    set_pshort("light steel greaves");
    set_long("A light pair of steel greaves, engraved upon them is an "+
      "image of a golden lion.\n");
    set_ac(15);
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_VOLUME,5000);
    add_prop(OBJ_I_WEIGHT,5000);
}
