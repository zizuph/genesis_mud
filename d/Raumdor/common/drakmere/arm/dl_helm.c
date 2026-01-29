inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_short("glowing holy helm");
    set_adj("glowing");
    add_adj("holy");
    set_long("This helm gleams with a bright inner light. It "+
    "has been blessed by the powers that be, giving divine protection "+
    "to the wearer.\n");
    set_ac(40);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 650);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 1000);

    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}
