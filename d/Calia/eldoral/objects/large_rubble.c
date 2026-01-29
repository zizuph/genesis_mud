#include "defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("stone");
    add_name("block");
    add_name(RUBBLE_NAME);
    set_adj("heavy");
    add_adj("cracked");
    set_short("heavy cracked stone");
    set_long("It's simply a large chunk of broken stone, rubble " +
        "fallen from the ruins.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 25000);
    add_prop(OBJ_I_VOLUME, 8000);
}
