inherit "/std/key";
#include <stdproperties.h>
#include "../defs.h"

create_key()
{
    set_key("cell_door_key");
    set_name("key");
    set_adj("heavy");
    add_adj("iron");
    set_long("Its a heavy iron key on a ring.\n");

    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 20);
}
