inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("sheet");
    set_adj(({ "plain", "white" }));
    set_long("A plain, white sheet.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 2);
}
