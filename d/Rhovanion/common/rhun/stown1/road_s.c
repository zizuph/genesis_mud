inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Edge of town");
    set_long("This rough dirt road leads out of town here, heading off " +
        "to the south.  You may also follow it north toward the center " +
        "of town.\n");

    AE(RHUN + "stown1/road_mid_s", "north");
    AE(RHUN + "roads/section2/a", "south");
}
