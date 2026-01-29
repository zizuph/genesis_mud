inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("toga");
    set_adj("fine");
    add_adj("woven");
    set_short("fine woven toga");
    set_long("This is a very finely woven toga that looks valuable.\n");
    set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,300);
}

