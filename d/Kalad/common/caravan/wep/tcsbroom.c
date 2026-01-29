#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("broom");
    set_adj("cleaning");
    set_long("A long handled broom used for sweeping floors.\n");
    set_hit(3);
    set_pen(10);
    set_hands(W_BOTH);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_VALUE,60);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);
}
