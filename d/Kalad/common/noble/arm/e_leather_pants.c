inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("pants");
    set_adj("expensive");
    add_adj("leather");
    set_short("expensive leather pants");
    set_long("These pants are made of very expensive, fine leather. "+
    "They are rare among the common folk.\n");
    set_ac(2);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,200);
    add_prop(OBJ_I_VALUE,180);
}

