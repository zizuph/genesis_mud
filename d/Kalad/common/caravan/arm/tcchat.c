#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("hat");
    set_adj("chef");
    set_long("This long floppy-looking hat belongs to the chef. Numerous "+
      "grease stains cover it.\n");
    set_ac(3);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,60);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,500);
}
