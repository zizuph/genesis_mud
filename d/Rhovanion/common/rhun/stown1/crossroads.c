inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Crossroads");
    set_long("This is a small crossroads at the north end of town.  " +
        "The dirt road continues on from east to west, with a branch " +
        "heading south through town.  Two buildings lie near here: a " +
        "large one to the north, and a smaller just to the southwest.\n");

    AE(RHUN + "stown1/guard_house", "north");
    AE(RHUN + "stown1/mayor_house", "southwest");
    AE(RHUN + "stown1/roadnw", "west");
    AE(RHUN + "stown1/roadne", "east");
    AE(RHUN + "stown1/road_mid_s", "south");

    add_item(({"building","buildings"}),
        "The buildings are made of wood, and appear open to the public.  " +
        "Why don't you step inside?\n");
}

