inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("nice");
    add_adj("paper");
    set_long("It looks like a ticket to the merchantline between Palanthas\n"+
      "and Grey Havens.\n");
    add_prop(OBJ_I_VALUE, 17);
}
