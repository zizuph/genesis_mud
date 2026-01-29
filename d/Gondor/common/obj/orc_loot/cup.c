/* A jewelry found on the random orc. */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_object()
{
    set_name("cup");
    add_name(({ "jewelry", "drinking-cup" }));
    set_adj("drinking");
    add_adj(({ "fine", "tin" }));
    set_short("drinking cup");
    set_long(BSN("A fine drinking cup, made of tin. On the bottom of the "+
    "cup a ship has been engraved."));    
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 125 + random(75));
}

query_recover()
{
    return MASTER;
}
