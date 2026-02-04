/* A shovel for the grave digger */
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

#define BSN(xx) break_string(xx + "\n", 70)

void
create_weapon()
{
    set_name("shovel");
    set_short("old shovel");
    set_long(BSN(
        "It is an old shovel. Suitable for digging, but could also, " +
        "less efficiently, crush a head or two."
    ));
    set_adj("old");
    set_hit(10);
    set_pen(8);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 10800);
    add_prop(OBJ_I_VOLUME, 2300);
    add_prop("mystic_weapon", 1);
}
