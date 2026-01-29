/*
 * Parent file for all flavours of tobacco, not meant to be cloned
 * by itself, but inherited into other cloned objects.
 */

inherit "/std/object";
#include "/sys/stdproperties.h"

void
create_object()
{
    set_name("tobacco");
    set_long("You shouldn't be seeing this; this object is incomplete.\n");
    set_short("A general tobacco");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 230);
}

int
query_is_tobacco()
{
    return 1;
}
