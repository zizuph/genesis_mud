inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    set_adj("polished");
    add_adj("steel");
    set_short("polished steel helm");
    set_long("This a very sturdy helm. It is polished like a mirror.\n");
    set_ac(25); 
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,2200);
}

