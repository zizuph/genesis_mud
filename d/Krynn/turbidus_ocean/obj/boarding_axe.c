inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    set_adj("steel");
    add_adj("boarding");
    set_short("boarding axe");
    set_long("This is a beautifully crafted axe used specifically " +
        "by sailors to scale the sides of a ship and to cut through " +
        "rigging. This axe is a particularly deadly fighting tool too, " +
        "as it has been crafted from the finest Ergothian steel and " +
        "kept razor sharp.\n");
    set_hit(35);
    set_pen(35);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 8000);
}
