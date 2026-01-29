inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Edge of town");
    set_long("This rough dirt road leads out of town here, heading off " +
        "to the west.  You may also follow it east, where it meets " +
        "others at a crossroads on the north end of town.  North of " +
        "here lies a small wooden house.\n");

    AE(RHUN + "stown1/homenw", "north");
    AE(RHUN + "roads/section1/a", "west");
    AE(RHUN + "stown1/crossroads", "east");

    add_item(({"building","house"}),
        "It appears you can easily step inside the small wooden house.  " +
        "Feel free to do so.\n");
}

