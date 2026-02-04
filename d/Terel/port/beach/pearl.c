inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("pearl");
    set_long("It is a pearl. It looks valuable.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 10);
}
