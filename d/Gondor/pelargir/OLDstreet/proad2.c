inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("a poor section of Pelargir");

    set_long(BSN("This area of Pelargir seems to be run down, and ill "
      + "used. There is a slight stench here that may be coming "
      + "from the docks east of here. "
      + "Another side road leads to the south, while this road runs "
      + "west to an orphanage and east to the docks. Above the "
      + "buildings you can see the Admiral's tower in the distance."));
    add_item("orphanage",
        "The orphanage does not look like a happy place.\n");
    add_admiral("north");

    add_exit(PELAR_DIR + "docks/dock7","east",0);
    add_exit(PELAR_DIR + "street/proad1","west",0);
    add_exit(PELAR_DIR+  "street/proad3","south",0);
}
