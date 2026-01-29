inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("blouse");
    set_adj("cotton");
    set_short("cotton blouse");
    set_long("This is a white cotton blouse that seems quite large and "+
    "open around the neck. It looks like it was made for someone with "+
    "a large bosom.\n");
    set_ac(4);
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,270);
    add_prop(OBJ_I_VALUE,10);
}

