inherit "/std/object";
#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>

void
create_object()
{
   set_name("ticket");
   add_name(TICKET_NAME);
   add_adj("blood-stained");
   add_adj("paper");
   set_long("It looks like a ticket to the merchantline between " +
      "Flotsam and Sparkle.\n");
   add_prop(OBJ_I_VALUE, 17);
}
