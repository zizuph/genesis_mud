/* A jewelry found on the random orc. */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_object()
{
    set_name("plate");
    add_name(({ "jewelry", "eating-plate" }));
    set_adj("tin");
    add_adj(({ "fine", "eating" }));
    set_short("tin plate");
    set_long(BSN("A fine eating plate, made of tin. On the plate "+
    "a ship has been engraved."));    
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 120);
    add_prop(OBJ_I_VALUE, 75 + random(50));
}
