inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_short("black");
    set_adj("tattered");
    set_short("tattered black robe");

    set_long("This is a large, black robe made of old, black "+
    "cloth. It covers you almost completely. Many old runes and "+
    "symbols cover it. In the center of the hood, there is etched "+
    "a grim skull within a pentagram.\n");

    set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 20);
    add_prop(OBJ_I_VOLUME, 130);
    add_prop(OBJ_I_WEIGHT, 200);
}
