#include "defs.h"
inherit "/std/weapon";

void
create_weapon()
{
    set_name("hammer");
    set_adj("carpenters");
    set_short("carpenters hammer");
    set_long(
      "It looks to be a common carpenters hammer, used mostly to drive " +
      "nails.\n");
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    set_hit(5);
    set_pen(5);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, COPPER_VALUE * 7);
    add_prop(OBJ_I_VOLUME, 90);
}
