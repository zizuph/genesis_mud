inherit "/d/Gondor/pelargir/lib/in_gate.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("inside the south gate of the city");
    set_long(BSN("The main street passes the city walls through the "
      + "south gate of Pelargir. To both sides of the gate the city "
      + "wall ends in a large tower, and between the two towers a "
      + "wide arch of stone spans across the street. At the southern "
      + "end of this archway are the two irons doors of the gate."));

    add_cobble();
    add_wall();

    add_exit(PELAR_DIR + "streets/belfalas11", "north", 0);
    add_exit(PELAR_DIR + "street/s_gate_e", "east", 0);
    add_exit(PELAR_DIR + "street/s_gate_w", "west", 0);

    create_gate("south");
}

