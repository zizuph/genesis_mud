/* One-handed standard arena sword */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    set_adj("steel");
    set_long("This is a standard one-handed arena broadsword. It looks " + 
        "fairly effective, while still being light.\n");
    set_default_weapon(30, 30, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 500);
}

