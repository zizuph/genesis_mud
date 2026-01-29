#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the Tharbad-Kalaman line");
    add_adj("torn");
    add_adj("dirty");
    set_long("It looks like a ticket to the boatline between Tharbad\n"+
      "and Kalaman.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 30);
}
