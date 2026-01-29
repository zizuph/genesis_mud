inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("scythe");
    set_pname("scythes");
    set_adj("harvesting");
    set_short("harvesting scythe");
    set_long(BS(
        "This is an agricultural tool used for harvesting " +
        "wheat. It isn't designed for combat but has a " +
        "sharp blade.",70));
    set_default_weapon(15, 15, W_POLEARM, W_SLASH, W_BOTH);
    add_prop(OBJ_I_VOLUME, 300);
}
