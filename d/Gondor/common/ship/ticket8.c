#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("The Harlond to Mithlond Line");
    add_adj("new");
    add_adj("silver");
    set_long("It looks like a ticket to the ship that sails between Harlond " +
        "and Mithlond. The ticket is silver and diamond shaped.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 18);
}
