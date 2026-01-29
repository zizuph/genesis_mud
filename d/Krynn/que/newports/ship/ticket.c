inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("red");
    set_long("This is a ticket for the boatline between Newports " +
      "and Sparkle.\n");
    add_prop(OBJ_I_VALUE, 20);
}
