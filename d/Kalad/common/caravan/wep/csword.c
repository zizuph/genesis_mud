#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("sword");
    set_adj("ornamented");
    add_adj("bastard");
    set_long("This sword is similar to a long sword, but has a longer "+
      "hilt. The pommel is engraved with a golden camel, indicating that "+
      "this is the possession of the captain of the city guard.\n");
    set_hit(31);
    set_pen(27);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE, 910);
    add_prop(OBJ_I_WEIGHT,7500);
    add_prop(OBJ_I_VOLUME,7500);
}
