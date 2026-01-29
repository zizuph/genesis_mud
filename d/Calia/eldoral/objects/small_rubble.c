#include "defs.h"

inherit "/std/object";

public void
create_object()
{
    set_name("stone");
    add_name("block");
    add_name(RUBBLE_NAME);
    set_adj("small");
    add_adj("jagged");
    set_short("small jagged stone");
    set_long("It's just a simple piece of grey stone about the " +
        "size of your fist. Rubble fallen from the walls somewhere " +
        "close by.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 1000);
}
