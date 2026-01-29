inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_adj("polished");
    add_adj("steel");
    set_short("pair polished steel bracers");
    set_long("These are a pair of very sturdy bracers made of finely "+
    "polished steel.\n");
    set_ac(25);
    set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT,1900);
    add_prop(OBJ_I_VOLUME,1000);
}

