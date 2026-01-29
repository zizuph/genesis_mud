inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Bridge to Esgaroth");
    set_long("This is the beginning of a small arched bridge.  It leads " +
        "east to the town of Esgaroth, and a small path goes west into " +
        "Mirkwood Forest.\n");
    add_exit("/d/Rhovanion/common/esgaroth/westbridge1", "east");
    add_exit(MIRK_DIR+"mirk-26-11-s", "west");
}
