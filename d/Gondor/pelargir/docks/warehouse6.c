inherit "/d/Gondor/pelargir/docks/warehouse";

#include "/d/Gondor/defs.h"

#define MAX_RATS 5 /* max number of rats running around */

void
create_warehouse()
{
    set_short("a large empty warehouse in Pelargir");
    set_long(BSN("From the inside, the warehouse is not much more than "
      + "a large hall. While there are many signs of recent work, the "
      + "hall is completely empty, if one ignores a few empty crates "
      + "stacked in a corner."));

    add_item("crates","The empty crates are just that - empty.\n");
    add_item("rats","You are sure they are hiding somewhere in the walls.\n");

    add_exit(PELAR_DIR+"docks/dock6", "north", 0);

    rats = allocate(MAX_RATS);
}

