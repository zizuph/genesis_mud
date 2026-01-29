#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("ticket");
    add_name("Poros-Tharbad Corsair Line");
    add_adj("black");
    add_adj("dirty");
    set_long("It looks like a ticket to the corsair running from\n" +
      "the Fords of Poros to Lebennin and Tharbad.\n");
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 30);
}
