inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("shield");
    set_adj("fine");
    add_adj("steel");
    set_short("fine steel shield");
    set_long("This is strong shield made of fine steel. It gleams like "+
    "new.\n");
    set_ac(21);     
    set_at(A_SHIELD);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2000);
}

