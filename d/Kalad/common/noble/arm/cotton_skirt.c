inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("skirt");
    set_adj("short");
    add_adj("cotton");
    set_short("short cotton skirt");
    set_long("This little white skirt barely covers your bum!\n");
    set_ac(1);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,150);
    add_prop(OBJ_I_VOLUME,100);
}

