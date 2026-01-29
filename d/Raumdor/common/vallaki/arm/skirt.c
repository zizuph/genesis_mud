inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("skirt");
    set_adj("short");
    set_short("short skirt");
    set_long("This is a short cotton skirt that would barely cover your "+
    "bottom.\n");
    set_ac(4);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,270);
    add_prop(OBJ_I_VALUE,10);
}

