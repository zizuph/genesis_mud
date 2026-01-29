#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("honeycomb");
    set_short("honeycomb");
    set_long("A piece of golden honeycomb made from industrious " +
        "honey bees.\n");
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
}

public int
query_the_honeycomb()
{
    return 1;
}
