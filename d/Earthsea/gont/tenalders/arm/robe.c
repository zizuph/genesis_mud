#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("robe");
    set_pname("robes");
    set_adj(({"old", "tattered"}));
    set_short("old tattered robe");
    set_pshort("old tattered robes");
    set_long("An old tattered robe, which is a bit "+
        "dirty and full of holes.\n");
    set_default_armour(5, A_ROBE, ({-2, -2,-2}), 0);
    add_prop(OBJ_I_WEIGHT,  350);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 65 + random(5));
}
