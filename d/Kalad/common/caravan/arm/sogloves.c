#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("pair of leather gloves");
    add_name("gloves");
    set_long("A nice set of gloves, they fit comfortably.\n");
    set_ac(5);
    set_at(A_HANDS);
    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 250);
}
