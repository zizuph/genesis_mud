#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("club");
    set_adj("thick");
    add_adj("beating");
    set_long("A thick, blood-covered club. It appears the overseer beats "+
      "his slaves with this weapon, thus the blood stains.\n");
    set_hit(12);
    set_pen(8);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_VALUE, 480);
    add_prop(OBJ_I_WEIGHT, 2250);
    add_prop(OBJ_I_VOLUME, 2500);
}
