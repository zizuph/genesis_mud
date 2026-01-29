#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("The Pelargir - Harlond River-line");
    add_adj("new");
    add_adj("blue");
    set_long("It looks like a ticket to the river boat running on the "
      + "Anduin between Pelargir and the Harlond, the harbour of Minas "
      + "Tirith.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 18);
}
