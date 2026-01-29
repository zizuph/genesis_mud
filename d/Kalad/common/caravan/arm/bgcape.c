#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("cape");
    set_adj("long");
    add_adj("silken");
    set_long("A beautiful cape trimmed with gold. On the back an image of a "+
      "golden coin with rays bursting from it has been sewn.\n");
    set_ac(3);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,480);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_WEIGHT,2000);
}
