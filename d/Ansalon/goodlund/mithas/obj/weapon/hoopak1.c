/* One-handed standard arena hoopak */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("hoopak");
    set_adj("short");
    set_long("This is a standard one-handed arena hoopak. It looks " + 
        "fairly effective, while still being light.\n");
    set_default_weapon(30, 30, W_POLEARM, W_BLUDGEON | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 500);
}

