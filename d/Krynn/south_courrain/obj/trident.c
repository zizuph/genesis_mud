/* Triton trident */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("trident");
    set_adj("bone");
    set_short("bone trident");
    set_long("This trident has been fashioned from the bones of a " +
        "great sea creature, and its three deadly tines from the " +
        "teeth of a dragon turtle!\n");
    set_default_weapon(30, 40, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 4000);
}

