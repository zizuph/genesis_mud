inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("boot");
    set_long(BS("This knife is small enough to fit in a boot " +
        "but it can be quite effective.",70));
    set_default_weapon(13, 11, W_KNIFE, (W_SLASH | W_IMPALE), W_ANYH);
    add_prop(OBJ_I_VOLUME, 160);
    add_prop(OBJ_I_WEIGHT, 2000);
}
