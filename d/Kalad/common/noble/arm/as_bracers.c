inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_adj("ancient");
    add_adj("steel");
    set_short("ancient steel bracers");
    set_long("These bracers cover your arms well. They look very old, "+
    "and ancient. As if they were passed down through many generations. "+
    "Some of the symbols on them date many hundreds of years back.\n");
    set_ac(26);
    set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT,2400);
    add_prop(OBJ_I_VOLUME,2000);
}

