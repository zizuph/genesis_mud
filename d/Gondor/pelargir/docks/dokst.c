inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("You are standing near the northern most dock of "
      + "Pelargir. To the north the Sirith river hurries past to join "
      + "the Anduin in its flow towards the sea. To the east it is "
      + "possible to step out on one of the docks where the ships "
      + "make port. South of here you may walk along the Sailor's "
      + "Boulevard, which runs along all the docks."));
    DOCKSHIPS;
    DOCKWA;
       add_item("sirith",BSN("The Sirith flows by you on the "+
          "north side, spilling out into the Anduin to the east."));
    add_exit(PELAR_DIR + "docks/dock1","east",0);
    add_exit(PELAR_DIR + "docks/dokst1","south",0);
    add_exit(PELAR_DIR + "docks/shipbldng","west",0);
}

