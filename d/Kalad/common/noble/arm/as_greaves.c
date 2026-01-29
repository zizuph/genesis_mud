inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("greaves");
    set_adj("ancient");
    add_adj("steel");
    set_short("pair of ancient steel greaves");
    set_long("These are a pair of old, ancient looking leg armours. "+
    "Many of the symbols on them date back many hundreds of years. It "+
    "looks sturdy, however.\n");
    set_ac(40); 
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,7200);
    add_prop(OBJ_I_VOLUME,6000);
}

