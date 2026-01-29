#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("straw");
    add_name("pile of straw");
    add_pname("piles of straw");
    set_short("pile of straw");
    set_pshort("piles of straw");
    set_long("A pile of dried yellow straw.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 0);
}
