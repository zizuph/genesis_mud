/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("at foot of mountains");
    set_long("You are at the foot of Misty Mountains. To the west you " + 
             "can see only huge peaks. The path goes through the saddle " +
             "high up. To the east there is a straight path towards dark " +
             "Mirkwood.\n");

    add_item("peak", "The peaks are high and dark.\n");
    add_item("peaks", "The peaks are high and dark.\n");
    add_item("saddle", "It is a natural saddle between two high peaks.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p12", "southwest",    0,    8);
    add_exit(ANDUIN_DIR + "oldpath1", "east", 0, 6);

}
