inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("platemail");
    set_adj("polished");
    add_adj("steel");
    set_short("polished steel platemail");
    set_long("This is a fine suit of platemail made of steel that "+
    "is polished to the point that they reflect your image as good "+
    "as a mirror.\n");
    set_ac(34);
    set_at(A_TORSO);
    add_prop(OBJ_I_WEIGHT,9600);
    add_prop(OBJ_I_VOLUME,7000);
}

