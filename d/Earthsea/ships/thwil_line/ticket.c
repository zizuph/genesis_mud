#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("ticket");
    add_name("_gont_port_oranea_");
    set_short("ticket");
    set_long("This is a ticket for transport on a ship. " +
        "It has a picture of a fiery red-scaled dragon " +
        "imprinted on the back.\n");
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_M_NO_SELL, 1);
}
