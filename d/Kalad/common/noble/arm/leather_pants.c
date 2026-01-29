inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("pants");
    set_adj("leather");
    set_short("leather pants");
    set_long("These are normal looking pants made of tanned leather.\n");
    set_ac(2);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,200);
}

