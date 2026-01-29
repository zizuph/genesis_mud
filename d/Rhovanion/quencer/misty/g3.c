inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <macros.h>

void
create_room()
{
    set_short("small path");
    set_long("You are on the small path that climbs the slope of Misty "+
             "Mountains. You can either go down west towards the valley "+
             "or crawl up northeast.\n");

    add_item("valley", "This is a fair green valley. Unlike the mountains " +
                       "ahead.\n");
    add_item("mountains", "Mountains look somehow dark. Maybe there is " +
                          "danger brooding there.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"g2", "west",    0,    3);
    add_exit("/d/Rhovanion/common/shield_guild/gates", "northeast", 0, 3);

}

