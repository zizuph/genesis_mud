inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Edge of town");
    set_long("This rough dirt road leads out of town here, heading off " +
        "to the east.  You may also follow it west, where it meets with " +
        "others at a crossroads on the north end of town.\n");

    AE(RHUN + "stown1/crossroads", "west");
    AE(RHUN + "roads/section3/a", "east");
}

