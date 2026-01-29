inherit "/d/Gondor/pelargir/lib/in_gate.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("inside the north gate of the city");
    set_long(BSN("Harlond Street passes the city walls through the "
      + "north gate of Pelargir. To both sides of the gate the city "
      + "wall ends in a large tower, and between the two towers a "
      + "wide arch of stone spans across the street. At the northern "
      + "end of this archway are the two iron doors of the gate."));

    add_cobble();
    add_wall();

    add_exit(PELAR_DIR + "streets/n_gate_e", "east", 0);
    add_exit(PELAR_DIR + "streets/belfalas01", "south", 0);
    add_exit(PELAR_DIR + "streets/n_gate_w", "west", 0);

    create_gate("north");
}

