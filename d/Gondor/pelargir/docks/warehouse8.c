inherit "/d/Gondor/pelargir/docks/warehouse";

#include "/d/Gondor/defs.h"

#define MAX_RATS 5 /* max number of rats running around */


void
create_warehouse()
{
    set_short("an old warehouse in Pelargir");
    set_long(BSN("This is an old large warehouse in the harbour "
      + "of Pelargir. A few empty crates are stacked in a corner, and "
      + "there is not much else here, except the squeaking of rats."));

    add_item("crates","The empty crates are just that - empty.\n");
    add_item("rats","You are sure they are hiding somewhere in the walls.\n");
 
    add_exit(PELAR_DIR+"docks/dock8","northeast",0);

    rats = allocate(MAX_RATS);
}

