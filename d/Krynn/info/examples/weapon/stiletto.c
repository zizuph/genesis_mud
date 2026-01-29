inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("stiletto");
    set_pname("stilettos");
    set_adj("small");
    set_long(BS("This is a thin bladeless knife with a very sharp point. " +
        "It's great for piercing chainmail and easily concealed.",70));
    set_default_weapon(14, 15, W_KNIFE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 140);
}
