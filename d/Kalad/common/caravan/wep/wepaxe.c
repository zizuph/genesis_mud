// 2021-11-07 Meton Changed from no-sell to keep
#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("axe");
    set_adj("volo");
    set_long("A fine-looking steel axe, with a nicely polished wooden "+
    "handle. Carved along the handle are the following words:\n"+
    "\n"+
    "Crafted by Volo, the Travelling Weapons Merchant.\n");
    set_hit(16);
    set_pen(20);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE, 720);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    //add_prop(OBJ_M_NO_SELL,1);
    set_keep(1);
}
