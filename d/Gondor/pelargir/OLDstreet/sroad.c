inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("You are on a rough cobblestone road, dividing the "
      + "poor section of Pelargir from the rest of the city. To the "
      + "east the road leads to the docks, from which you can "
      + "detect a faint odor of fish, and a split turns into the "
      + "Sailor's Boulevard to the north. The road leads deeper "
      + "into the city to the west, with the poor section on the "
      + "south side of the street."));
    COBBLE;
    add_item("docks", BSN("Lots of traffic comes "+
          "from the direction of the docks, most likely it is "+
          "an interesting place (despite the odor)."));
    add_item("poor section",BSN("That looks like the "+
          "bad part of town, a bit of crime and unrest there "+
          "you can be sure."));
    add_exit(PELAR_DIR + "docks/dokst4","north",0);
    add_exit(PELAR_DIR + "docks/dock6","east",0);
    add_exit(PELAR_DIR + "street/sroad1","west",0);
}
