inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("yathesearethem");
    add_name("seeds");
    set_adj("silver");
    add_adj("small");
    set_short("handful of small silver seeds");
    set_long("These strange silver seeds sparkle in the light, but "+
    "you don't know what they would grow if you sprinkled them "+
    "somewhere.\n");
    add_prop(OBJ_M_NO_BUY,"You can't.\n");
}

