inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("apron");
    set_adj("stained");
    set_short("stained apron");
    set_long("Big, greasy stains cover this dirty apron.\n");
    set_ac(1);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
}

