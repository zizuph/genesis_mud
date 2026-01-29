#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("shirt");
    set_adj("raggedy");
    set_long("A torn cloth shirt, greasy stains cover most of it.\n");
    set_ac(3);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,24);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,1000);
}
