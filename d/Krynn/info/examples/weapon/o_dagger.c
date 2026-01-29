inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("dagger");
    set_pname("daggers");
    set_adj("ornamental");
    set_long(BS("This dagger is studded with jewels. From the feel " +
        "of it, it was made more to look nice than to handle well." +
        " It was probably stolen.",70));
    set_default_weapon(12, 13, W_KNIFE, (W_SLASH | W_IMPALE), W_ANYH);
    add_prop(OBJ_I_VOLUME, 160);
    add_prop(OBJ_I_VALUE, 600);
    add_prop(OBJ_I_WEIGHT, 1000);
}
