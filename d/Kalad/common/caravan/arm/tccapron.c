#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("apron");
    set_adj("greasy");
    add_adj("leather");
    set_long("This cooking apron must belong to the chef, simply because "+
      "of all the grease stains on it.\n");
    set_ac(6);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,120);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,2000);
}
