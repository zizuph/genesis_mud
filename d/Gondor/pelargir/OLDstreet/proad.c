inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("a poor section of Pelargir");
    set_long(BSN("This is a poorly lit street in southern Pelargir. "
      + "To the west lies a pile of trash and debris so big it blocks "
      + "the road. To the east the road continues on past an "
      + "orphanage to the docks, and to the north a small side street "
      + "leads to the main road."));
    add_item(({"trash","debris","trash and debris"}),BSN("The "
      + "pileup blocks the road so perfectly it seems that "
      + "it must be intentional. If it didn't stink so bad "
      + "and attract so many disguisting vermin, you might "
      + "be curious as to what is on the other side."));
    add_item("orphanage",
        "The orphanage does not look like a happy place to be.\n");

    add_exit(PELAR_DIR + "street/sroad1","north",0);
    add_exit(PELAR_DIR + "street/proad1","east",0);
}
