/* Two-handed standard arena sword */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    set_adj("steel");
    set_long("This is a standard two-handed arena longsword. It looks " + 
        "very effective, while a bit heavy.\n");
    set_default_weapon(40, 40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
}

