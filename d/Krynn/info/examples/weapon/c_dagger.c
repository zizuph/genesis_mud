inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("dagger");
    set_pname("daggers");
    set_adj("curved");
    set_long(BS("This dagger is wickedly curved. Being cut by it " +
        "would be quite painful.",70));
    set_default_weapon(14, 16, W_KNIFE, (W_SLASH | W_IMPALE), W_ANYH);
    add_prop(OBJ_I_VOLUME, 160);
    add_prop(OBJ_I_WEIGHT, 3000);
}
