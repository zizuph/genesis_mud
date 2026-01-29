#pragma strict_types

#include "defs.h"
#include "/d/Ansalon/common/defs.h"
#include DL_CLOCK

inherit TEMPLE + "std_temple.c";

string
day_night_desc()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
        case TOD_TWILIGHT:
            return "the night almost blend with the two stalactites " +
                "hanging from the ceiling";
        case TOD_DAWN:
        case TOD_DAY:
            return "shadows fall from the two stalactites hanging from " +
                "ceiling";
    }
}

void
create_temple_room()
{
    ::create_temple_room();

     set_short("Inside the entrance of the temple");
    set_long("You are standing in a section of a narrow corridor " +
        "that widens up further south where it leads into torchlit " +
        "darkness into the temple. North a square opens up where " +
        "@@day_night_desc@@.\n");

    add_item(({"stalactites", "stalactite"}), "At the very northernmost " +
        "part of the entrance hangs two stalactites from the rough " +
        "stone ceiling, resembling the open maw of some beast.\n");

    add_item("ceiling", "It is rough and made of stone. Where it meets " +
        "the corridor in the south it appears to be more finer cut where " +
        "a darkness begins to shroud it.\n");

    add_item(({"city", "neraka"}),
        "You look towards the entrance and beyond the guards you catch a " +
        "small glimpse of the city outside.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is narrow and seemingly straight, leading " +
        "towards the centre of the temple where it widens up.\n");

    add_exit( NINNER + "s5", "north" );
    add_exit( TEMPLE + "corr1.c", "south" );
}

