#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("broadsword");
    add_name("sword");
    set_adj("keen");
    set_long("A keen-edged broadsword that looks excellent for cleaving "+
      "apart flesh. Wrapped around the hilt is an image of a golden lion.\n");
    set_hit(28);
    set_pen(27);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,3000);
}
