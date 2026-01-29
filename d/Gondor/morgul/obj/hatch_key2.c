inherit "/std/key";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tunnel/tunnel_door.h"

void create_key()
{
    add_name(HATCH_KEY2);
    set_adj(({"rusty","iron"}));
    set_long("An rusty iron key.\n");
    set_key(HATCH_KEY2);

    add_prop(OBJ_I_WEIGHT,270);
    add_prop(OBJ_I_VOLUME,40);
    add_prop(OBJ_I_VALUE,25);
}
