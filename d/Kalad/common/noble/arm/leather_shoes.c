inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("shoes");
    set_adj("shiny");
    add_adj("leather");
    set_short("pair of shiny leather shoes");
    set_long("These are very fine shoes made of good leather that is "+
    "polished like mirrors.\n");
    set_ac(3);
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,80);
}

