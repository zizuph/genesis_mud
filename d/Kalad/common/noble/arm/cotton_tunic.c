inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("tunic");
    set_adj("cotton");
    set_short("cotton tunic");
    set_long("This tunic is made of fresh white cotton.\n");
    set_ac(1);
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
}

