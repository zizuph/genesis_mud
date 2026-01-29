inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("white");
    set_long("It looks like a ticket to the merchantline between Palanthas\n"+
      "and Cove.\n");
    add_prop(OBJ_I_VALUE, 18);
}
