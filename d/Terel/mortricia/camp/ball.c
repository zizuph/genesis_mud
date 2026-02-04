/*
    A ball for jogglers
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("ball");
    set_short("ball");
    set_long("It's a ball.\n");
    add_prop(OBJ_I_VALUE, 10 + random(11));
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

