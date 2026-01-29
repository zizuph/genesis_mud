inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */

void
create_weapon()
{
    ::create_weapon();
    set_name("hammer");
    set_adj("huge");
    add_adj("iron");
    set_short("huge iron hammer");
    set_long("This is one HUGE hammer.\n");
    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);
    set_hands(W_BOTH);
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,6000);
    add_prop(OBJ_I_VALUE,300);
}
