inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("bracers");
    set_adj("fine");
    add_adj("steel");
    add_adj("chain");
    set_short("pair of fine steel chain bracers");
    set_pshort("pairs of fine steel chain bracers");
    set_long("There are chain sleves made of fine interlinking chain "+
    "links that go up to your shoulders, down to your wrists.\n");
    set_ac(22); /* +2 because of the fine steel it is made of */
    set_am(({-2,3,-1}));
    set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT,1900);
    add_prop(OBJ_I_VOLUME,1000);
}

