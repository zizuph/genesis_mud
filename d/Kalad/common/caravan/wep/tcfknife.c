#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("knife");
    set_adj("falconer");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_short("falconer knife");
    set_long("A long-bladed knife used by falconers and other outdoorsmen "+
      "as an all purpose tool, one purpose being to kill their enemies with "+
      "it.\n");
    set_hit(10);
    set_pen(11);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_VALUE,540);
    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,2500);
}
