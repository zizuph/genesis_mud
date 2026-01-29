#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("street in western Osgiliath");
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("no");
    set_extraline("The street continues southwest towards the edge of the "+
        "ruined city, while it leads to the stone bridge of the city to the "+
        "northeast. On both sides of the street there are ruined buildings, "+
        "nobody has been living here for many years.");
    add_exit(OSG_DIR + "wbridge1", "northeast", 0, 2);
    add_exit(OSG_DIR + "wosg4",    "south",     0, 2);
    add_exit(OSG_DIR + "wosg1",    "southwest", 0, 2);
    add_exit(OSG_DIR + "wosg2",    "west",      0, 2);
}

