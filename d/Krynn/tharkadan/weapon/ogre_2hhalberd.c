inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("halberd");
    set_adj("iron");
    add_adj("cold-iron");
    add_adj("huge");
    set_short("huge cold-iron halberd");
    set_long("This is a huge two-handed halberd made of cold iron. " +
        "While there are signs of the previous owner not taking great " +
        "care of this weapon, it is clearly made by a skilled dwarven " +
        "weaponsmith. The style of its make would indicate it is an old " +
        "polearm, likely from the days of the Dwarfgate Wars.\n");
    set_default_weapon(35, 40, W_POLEARM, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 24000);
}
