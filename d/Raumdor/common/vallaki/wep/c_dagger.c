inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */

void
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("slim");
    set_short("slim dagger");
    set_long("This is a slim, sharp dagger made of steel.\n");
    set_dt(W_SLASH);
    set_wt(W_KNIFE);
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1200);
    add_prop(OBJ_I_VALUE,200);
}
