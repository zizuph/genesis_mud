/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("small path");
    set_long("You are on the path, south above the valley. The path climbs up "+
             "east to the Misty Mountains.\n");

    add_item("valley", "This is a fair green valley. Unlike the mountains " +
                       "ahead.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
                          "danger brooding there.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"g1", "northwest",    0,    3);
    add_exit(MISTY_DIR+"g3", "east",    0,    3);

}

