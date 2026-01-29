/* One-handed standard arena knife */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("long");
    set_long("This is a standard one-handed arena knife. It looks " + 
        "fairly effective, while still being light.\n");
    set_default_weapon(20, 20, W_KNIFE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 400);
}

