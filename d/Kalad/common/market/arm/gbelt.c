inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* A Sarr Industries production */

void
create_armour()
{
    ::create_armour();
    set_name("belt");
    set_adj("black");
    add_adj("garter");
    set_short("black garter belt");
    set_long("A very sexy garter belt.\n");
    set_ac(1);
    set_at(A_WAIST);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,15);
    add_prop(OBJ_I_VALUE,8);
}

