inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("along Sailors' Boulevard");
    set_long(BSN("This is Sailors' Boulevard. Along this stretch you "
      + "can find all sorts of sailors and their hangouts. To the east "
      + "are the vast docks of Pelargir, and to the south the "
      + "boulevard comes to an end as it meets one of the main streets "
      + "of Pelargir. On the corner stands a warehouse."));
    add_dockships();
    add_cobble();

    add_item(({"house", "warehouse", }), BSN(
        "It is a large warehouse, probably used by merchants to store "
      + "goods that are to be loaded on ships going to far away "
      + "countries or that are landed here by ships coming to Pelargir."));

    add_exit(PELAR_DIR + "docks/dokst3","north",0);
    add_exit(PELAR_DIR + "docks/dock5","east",0);
    add_exit(PELAR_DIR + "street/sroad","south",0);
    add_exit(PELAR_DIR + "docks/warehouse4", "west", 0);
}
