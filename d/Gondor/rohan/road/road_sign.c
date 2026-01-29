inherit "/std/scroll";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_scroll()
{
  set_name("sign");
  set_adj("large");
  add_adj("onyx");
  set_long(BSN("The sign is made of pure onyx. All the written runes on the sign " +
    "are made of sterling silver. The poles are, of course, made of white polished marble. "));
  set_file(ROH_DIR+"road/roadsign.txt");
  add_prop(OBJ_M_NO_GET, "The sign is stuck in the ground.\n");
}
