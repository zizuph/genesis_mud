inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("sword");
    set_adj("iron");
    add_adj("cold-iron");
    add_adj("two-handed");
    set_short("two-handed cold-iron sword");
    set_long("This is a massive two-handed sword made of cold iron. " +
        "While there are signs of the previous owner not taking great " +
        "care of this blade, it is clearly made by a skilled dwarven " +
        "weaponsmith. The style of its make would indicate it is an old " +
        "blade, likely from the days of the Dwarfgate Wars.\n");
    set_default_weapon(37, 39, W_SWORD, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 24000);
}
