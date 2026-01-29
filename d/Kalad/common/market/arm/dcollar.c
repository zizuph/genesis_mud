inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* dog collar by Sarr */
void
create_armour()
{
    ::create_armour();
    set_name("collar");
    set_adj("studded");
    add_adj("leather");
    set_long(
     "This collar is made of black leather. Silver studs adorn its length.\n");
    set_ac(5);
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,40);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,20);
}

