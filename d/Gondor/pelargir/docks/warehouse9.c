inherit "/d/Gondor/pelargir/docks/warehouse";

#include "/d/Gondor/defs.h"

#define MAX_RATS 6 /* max number of rats running around */

void
create_warehouse()
{
    set_short("a derelict warehouse in Pelargir");
    set_long(BSN("This is a large derelict warehouse in the harbour "
      + "of Pelargir. A few empty crates are stacked in a corner, and "
      + "there is not much else here, except the squeaking of rats."));

    add_item("crates","The empty crates are just that - empty.\n");
    add_item("rats","You are sure they are hiding somewhere in the walls.\n");

    add_exit(PELAR_DIR+"docks/dock9","northeast",0);

    rats = allocate(MAX_RATS);
}

