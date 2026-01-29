#include "../default.h"
inherit (STD + "weapon");

#include <wa_types.h>

void
create_weapon()
{
    ::create_weapon();

    set_name("knife");
    set_adj("butcher");
    set_long("A large knife used to butcher small animals with. Blood is "+
      "stained all over the blade.\n");
    set_hit(6);
    set_pen(10);
    set_wt(W_KNIFE);
    set_dt(W_SLASH);
    add_prop(OBJ_I_VALUE,240);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
}
