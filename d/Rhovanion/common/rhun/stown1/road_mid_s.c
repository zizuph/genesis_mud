inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Middle of town");
    set_long("The road leads north-to-south here at the center of town.  " +
        "East of here lies a small wooden house.  To the southwest is an " +
        "old, run-down inn.  It is closed now; it's doors locked to the " +
        "public.\n");

    AE(RHUN + "stown1/crossroads", "north");
    AE(RHUN + "stown1/road_s", "south");
    AE(RHUN + "stown1/homese", "east");

    add_item(({"building","buildings"}),
        "Which building do you want to look at?  The house of the inn?\n");

    add_item(({"house","home"}),
        "The small wooden house is open.  Why don't you step inside " +
        "and take a look around?\n");

    add_item("inn",
        "The inn is quite run down, and seems to have been closed some " +
        "time ago.\n");
}

