inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("along a poor street in Pelargir");

    set_long(BSN("The road takes a dramatic turn among the fisherman's "
      + "shacks here. To the west the road leads farther into the poor "
      + "southern section of Pelargir, and to the north you can see "
      + "one of the docks. Above the din, to the northwest, you can "
      + "see the Admiral's tower."));
    PADMIRAL;
    PBUILD;

    add_exit(PELAR_DIR + "street/proad4","west",0);
    add_exit(PELAR_DIR + "homes/shack3","northwest",0);
    add_exit(PELAR_DIR + "docks/dock8","north",0);
}
