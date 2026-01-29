inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("warhammer");
    add_name("hammer");
    add_name("club");
    set_adj("iron");
    add_adj("cold-iron");
    add_adj("two-handed");
    set_short("two-handed cold-iron warhammer");
    set_long("This is a massive two-handed warhammer made of cold iron. " +
        "While there are signs the previous owner not taking great care " +
        "of this weapon, it is clearly made by a skilled dwarven " +
        "weaponsmith. The style of its make would indicate it is an " +
        "old hammer, likely from the days of the Dwarfgate Wars.\n");
    set_default_weapon(37, 40, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 24000);
}
