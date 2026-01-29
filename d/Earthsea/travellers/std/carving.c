#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_carving()
{
}

public nomask void
create_object()
{
    set_name("carving");
    set_adj(({ "miniature", "wooden" }));

    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VALUE, 1);
    
    create_carving();
}
