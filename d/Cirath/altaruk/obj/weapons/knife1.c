inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("sharp");
    set_adj("bone");
    set_short("sharp bone knife");
    set_long("A sharp knife made from the bones of some animal.\n");

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15,10) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10,W_KNIFE) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    set_hit(15);
    set_pen(10);

    set_wt(W_KNIFE);
    set_dt(W_SLASH|W_IMPALE);

    set_hands(W_ANYH);

}
