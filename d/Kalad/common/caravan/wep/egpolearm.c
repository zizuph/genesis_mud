#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("pike");
    set_adj("keen");
    add_adj("awl");
    set_long("A long-shafted weapon whose handle is carved out of solid "+
      "redwood from the Hespyre mountains. At the end of its twelve foot "+
      "length is a tapered spear head. An image of a golden lion is marked "+
      "upon it.\n");
    set_hit(21);
    set_pen(28);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_VALUE,333);
    add_prop(OBJ_I_WEIGHT,6000);
    add_prop(OBJ_I_VOLUME,6000);
}
