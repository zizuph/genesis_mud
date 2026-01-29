#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("light chain helm");
    add_name("helm");
    set_long("This helm is light and durable and seems to afford a reasonable "+
      "amount of protection.\n");
    set_ac(10);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 240);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 1500);
}
