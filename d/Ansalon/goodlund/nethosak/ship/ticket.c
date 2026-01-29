inherit "/std/object";
#include "/d/Ansalon/goodlund/nethosak/ship/local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("clean");
    add_adj("paper");
    set_long("It looks like a ticket to the shipline between " +
      "Flotsam and Mithas.\n");
    add_prop(OBJ_I_VALUE, 17);
}
