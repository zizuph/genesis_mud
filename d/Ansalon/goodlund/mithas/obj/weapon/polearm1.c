/* One-handed standard arena spear */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("spear");
    set_adj("long");
    set_long("This is a standard one-handed arena spear. It looks " + 
        "fairly effective, while still being light.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 500);
}

