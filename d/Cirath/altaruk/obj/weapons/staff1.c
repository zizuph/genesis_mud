inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("staff");
    set_pname("staves");
    set_adj("agafari");
    set_adj("wood");
    set_long("A long hardwood staff made from the agafari tree.\n");

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15,10) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(10,W_POLEARM) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    set_hit(15);
    set_pen(10);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

}
