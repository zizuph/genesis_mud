/* Two-handed standard spear */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("spear");
    set_adj("bone");
    add_adj("whalebone");
    set_short("whalebone spear");
    set_long("This is a spear beautifully carved from a whale bone, " +
        "and is a favoured weapon of the aquatic race of the Courrain " +
        "Ocean known as the tritons.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 4000);
}

