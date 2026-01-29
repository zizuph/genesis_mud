#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("halberd");
    set_adj("serrated");
    set_long("A wickedly edged halberd with edges that look razor sharp. "+
      "On the handle of the weapon is engraved the symbol of the "+
      "trading company, A gold coin with lines radiating from it.\n");
    set_hit(24);
    set_pen(34);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE,600);
    add_prop(OBJ_I_WEIGHT,16000);
    add_prop(OBJ_I_VOLUME,16000);
}
