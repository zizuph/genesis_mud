/*
    A skull. Mortricia 920910
 */
inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("skull");
    set_short("skull");
    set_long(break_string(
        "It's a human skull.\n", 70));
    set_adj("human");
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
