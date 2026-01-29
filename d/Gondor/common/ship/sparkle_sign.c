#pragma save_binary

inherit "/std/scroll";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_scroll()
{
  set_name("sign");
  set_adj("large");
  add_adj("wooden");
  set_long("The wooden sign has been placed on one end of the pier. Some words\n"+
    "have been carved into it, thereafter to be painted in black.\n");
  set_file(SHIP_DIR+"sparkle.txt");
  add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}