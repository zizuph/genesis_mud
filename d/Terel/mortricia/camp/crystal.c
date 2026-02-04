/*
    A crystal ball.
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("crystal");
    set_short("spherical crystal");
    set_long(break_string(
        "It's a spherical crystal. When you look into it " +
        "you see nothing but a compact darkness.\n", 70));
    set_adj("spherical");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VALUE, 200 + random(11));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 800);
}

