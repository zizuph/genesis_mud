/* Two-handed standard arena axe */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_adj("steel");
    set_long("This is a standard two-handed arena battleaxe. It looks " + 
        "very effective, while a bit heavy.\n");
    set_default_weapon(40, 40, W_AXE, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
}

