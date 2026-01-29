// 2021-11-07 Meton Changed from no-sell to keep
#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("club");
    set_adj("volo");
    set_long("A good-sized steel club bearing the following inscription at "+
      "its base:\n"+
      "\n"+
      "Crafted by Volo, the Travelling Weapons Merchant.\n");
    set_hit(20);
    set_pen(18);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_VALUE, 1440);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 4000);
    //add_prop(OBJ_M_NO_SELL,1);
    set_keep(1);
}
