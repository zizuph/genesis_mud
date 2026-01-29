/* by Antharanos */
#include "defs.h"
inherit "/std/scroll";

void
create_scroll()
{
    set_name("map");
    set_adj("large");
    set_short("large map");
    set_long(
      "It is a large map that says \"Raumdor\" at the top.\n");
    add_prop(OBJ_I_VALUE, GOLD_VALUE * 2);
    set_file(DOC_DIR + "MAPS/Raumdor.txt");
}
