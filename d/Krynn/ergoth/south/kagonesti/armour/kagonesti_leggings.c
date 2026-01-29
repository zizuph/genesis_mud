#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void create_armour()
{
    int ac;

    set_name("leggings", 1);
    add_name("pair");
    set_adj("leather");
    set_short("pair of leather leggings");
    set_pshort("pairs of leather leggings");
    set_long("This pair of leggings was made by the Kagonesti elves from "
        + "tanned animal hide. The leather has been hardened to provide "
        + "extra protection.\n");

    ac = random(10);
    set_ac(6 + ac);
    set_at(A_LEGS);
    set_am(({0, 1, -1}));
    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_I_WEIGHT, ac*113);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}
