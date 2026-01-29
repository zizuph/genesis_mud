#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("The Gondor - Kalad trade-line");
    add_adj("torn");
    add_adj("brown");
    set_long("It looks like a ticket to the merchant ship running between Pelargir\n"+
      "in Gondor, and Kalad.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 28);
}
