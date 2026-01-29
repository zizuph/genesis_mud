/* Two-handed standard arena pike */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("hoopak");
    set_adj("sturdy");
    set_long("This is a standard two-handed arena hoopak. It looks " + 
        "very effective, while a bit heavy.\n");
    set_default_weapon(40, 40, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
}

