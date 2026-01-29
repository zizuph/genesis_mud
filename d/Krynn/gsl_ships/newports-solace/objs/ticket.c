inherit "/std/object";
#include "local.h"

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("green");
    set_long("This green ticket grants passage between Solace " +
        "and Newports.\n");
    add_prop(OBJ_I_VALUE, 5);
}
