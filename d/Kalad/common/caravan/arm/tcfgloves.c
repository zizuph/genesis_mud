#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("gloves");
    set_adj("falconer");
    set_long("These hardened leather gloves are used by falcon-tamers as a "+
      "portable perch for their falcons.\n");
    set_ac(10);
    set_at(A_HANDS);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_WEIGHT,750);
}
