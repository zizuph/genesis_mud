inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("stamped");
    set_long("It looks like a ticket for the ferry between " +
      "Kalaman and Vingaard Keep. It has a stamp of the " +
      "kingfisher on it.\n");
    add_prop(OBJ_I_VALUE, 17);
}
