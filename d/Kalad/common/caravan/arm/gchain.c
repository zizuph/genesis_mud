#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("light chainmail");
    add_name("chainmail");
    add_name("mail");
    set_long("This suit of chainmail armour looks sturdy, yet is relatively "+
      "light in weight.\n");
    set_ac(20);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 450);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
