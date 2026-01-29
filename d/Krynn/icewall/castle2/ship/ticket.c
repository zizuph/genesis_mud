inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("small");
    add_adj("paper");
    set_long("This is a ticket for the schooner that runs between Palanthas " +
      "and Icewall.\n");
    add_prop(OBJ_I_VALUE, 20);
}
