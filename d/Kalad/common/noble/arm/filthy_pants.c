inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("pants");
    set_adj("filthy");
    set_short("filthy pants");
    set_long("Filthy and old, these pants don't look like anyone cares "+
    "about them. Thre are large holes on the knees.\n");
    set_ac(2);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,200);
}

