#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("narrow street in western Osgiliath");
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_extraline("You are standing amongst the ruins of the west part of "+
        "Osgiliath. The narrow street leads west out of the ruined city, "+
        "while it continues east to the main street.");
    add_exit(OSG_DIR + "wosg3",    "east", 0, 2);
    add_exit(ANO_DIR + "road/or3", "west", 0, 2);
}

