#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("leather boots");
    add_name("boots");
    set_long("A handsome pair of leatherbound boots, they look quite "+
      "comfortable.\n");
    set_ac(5);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE, 140);
    add_prop(OBJ_I_VOLUME, 750);
    add_prop(OBJ_I_WEIGHT, 750);
}
