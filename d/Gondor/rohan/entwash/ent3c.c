inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void
create_swamp()
{
    set_extra_long("A number of streams come together here as"
      + " they make their way toward the river Anduin, which seems to"
      + " be a short distance yet to the north. You hear some quiet"
      + " lapping of water in that direction.");

    add_item(({"streams","stream"}), BSN("Two streams flow together"
      + " here, one from the south, and one from the southeast. They"
      + " wind their way into the silent mist to the north."));

    add_exit(ENTWASH_DIR + "ent3b", "southwest");
    add_exit(ENTWASH_DIR + "ent3d", "south");
}
