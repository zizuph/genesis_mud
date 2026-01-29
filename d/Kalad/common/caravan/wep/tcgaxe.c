#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("axe");
    set_adj("wicked");
    add_adj("serrated");
    set_long("A wickedly edged axe with edges that look razor sharp. "+
      "On the handle of the weapon is engraved the symbol of the "+
      "trading company, A gold coin with lines radiating from it.\n");
    set_hit(25);
    set_pen(27);
    set_hands(W_BOTH);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_WEIGHT,12000);
    add_prop(OBJ_I_VOLUME,12000);
}
