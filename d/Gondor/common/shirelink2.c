#pragma save_binary

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(9);
    set_areadesc("wastelands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The empty plains stretch to the horizon in every " +
        "direction. Only to the southwest some hills are rising. " +
        "Over the plains runs a narrow track from northwest to " +
        "southeast.\n");
    add_item(({"hill", "hills"}), 
        "The hills to the southwest must be the Emyn Muil, the " +
        "hill country that lies between the Anduin and the wastelands " +
        "north of Mordor.\n");
    add_item(({"plain", "plains"}), 
        "The plains continue right to the horizon in all direction " +
        "except for the southwest where some hills can be seen. " +
        "These are the Brown Lands, desolate and treeless, between " +
        "Mirkwood to the north and the desolation north of Mordor " +
        "to the south.\n");
    add_item(({"path", "track"}), 
        "The track is running from the northwest to the southeast. " +
        "It looks ancient and little used.\n");
    add_exit("/d/Shire/common/gondorlink2", "northwest", 0, 5);
    add_exit(ITH_DIR + "dagorlad/path5", "southeast", 0, 5);
}

string
short_desc()
{
    if (areatype != 9)
        return ::short_desc();

    return "Barren "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
}
