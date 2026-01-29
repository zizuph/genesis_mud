#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("Earendil Shipping Service");
    add_adj("torn");
    set_long(break_string("It is a ticket for the boat that goes from Pelargir in Gondor to Faerie.\n",70));
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 30);
}
