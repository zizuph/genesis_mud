/* One-handed standard arena axe */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_adj("steel");
    set_long("This is a standard one-handed arena axe. It looks " + 
        "fairly effective, while still being light.\n");
    set_default_weapon(30, 30, W_AXE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 500);
}

