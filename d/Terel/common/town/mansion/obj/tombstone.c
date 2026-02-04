inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


create_object()
{
    set_name("tombstone");
    add_name("stone");
    set_short("old tombstone");
    set_adj("old");
    set_long(break_string(
        "It is an old tombstone. You do not know who is buried " +
        "here since you cannot find any inscription on it.\n"
    , 72));
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 40000);
    add_prop(OBJ_M_NO_GET, 1);
}
