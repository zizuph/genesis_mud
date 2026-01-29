inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("token");
    add_name("ticket");
    add_name(TICKET_NAME);
    set_adj("black");
    add_adj("wooden");
    set_long("This is a small black wooden token that gives passage on " +
        "the troop ferry between Newports and Sanction.\n");
    add_prop(OBJ_I_VALUE, 10);
}
