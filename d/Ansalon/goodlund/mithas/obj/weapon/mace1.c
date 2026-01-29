/* One-handed standard arena mace */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("mace");
    set_adj("light");
    set_long("This is a standard one-handed arena mace. It looks " + 
        "fairly effective, while still being light.\n");
    set_default_weapon(30, 30, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 500);
}

