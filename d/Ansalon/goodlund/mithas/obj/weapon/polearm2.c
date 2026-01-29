/* Two-handed standard arena pike */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("pike");
    set_adj("long");
    set_long("This is a standard two-handed arena pike. It looks " + 
        "very effective, while a bit heavy.\n");
    set_default_weapon(40, 40, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
}

