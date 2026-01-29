inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("fine");
    add_adj("steel");
    add_adj("plate");
    set_short("fine steel plate helm");
    set_long("This helm is made of very fine, strong alloyed steel. "+
    "It has a face-guard with a beak-like nose point.\n");
    set_ac(22); /* +2 because of the fine steel it is made of */
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,2400);
    add_prop(OBJ_I_VOLUME,1200);
}

