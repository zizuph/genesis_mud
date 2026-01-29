inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("petal");
    set_adj("white");
    add_adj("flower");
    set_short("white flower petal");
    set_long("This is a small, white flower petal, that looks like "+
    "it comes from a blossoming apple tree.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_VALUE,0);
}

