inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("blade");
    add_name("knife");
    set_adj("short");
    set_adj("curved");
    set_short("short curved blade");
    set_long("A short curved knife made from a claw of some sort.\n");

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25,20) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(20,W_KNIFE) + random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    set_hit(25);
    set_pen(20);

    set_wt(W_KNIFE);
    set_dt(W_SLASH);

    set_hands(W_ANYH);

}
