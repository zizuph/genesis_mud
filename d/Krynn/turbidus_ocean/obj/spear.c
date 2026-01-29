/* One-handed standard arena spear */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("spear");
    set_adj("coral");
    set_short("coral spear");
    set_long("This nasty jagged spear is a favoured weapon of the " +
        "sahuagin, a shark-like humanoid that terrorises the seas " +
        "of Krynn.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 4000);
}

