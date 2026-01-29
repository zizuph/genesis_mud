#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the Gondorian line");
    add_adj("torn");
    set_long("It looks like a ticket to the boatline between Pelargir\n"+
      "and Sparkle.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 30);
}
