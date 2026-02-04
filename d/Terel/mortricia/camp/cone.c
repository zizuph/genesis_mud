/*
    A cone for jogglers
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("cone");
    set_short("cone");
    set_long("It's a cone.\n");
    add_prop(OBJ_I_VALUE, 10 + random(11));
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

