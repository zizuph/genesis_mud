#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Shire/sys/flags.h"

void
create_area_room()
{
    set_areatype(9);
    set_areadesc("wastelands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The ground is falling away sharply from the cliffs " +
        "of the Emyn Muil to the west. A great fissure is yawning to " +
        "the east. Large boulders are all what lies on bare stony " +
        "slopes. Between the fissure and the cliffs, you can only " +
        "go either south or north.\n");
    add_item(({"cliff", "cliffs", "emyn muil"}), 
        "To the west rise the steep cliffs of the Emyn Muil, the " +
        "hills that lie between the Anduin and the wastelands north " +
        "of Mordor. The cliffs are sheer and almost smooth, so it is " +
        "impossible to climb them.\n");
    add_item(({"fissure"}), 
        "The fissure yawning to the east is not wide, but too wide " +
        "to jump across. There might be water gurgling in its depth.\n");
    add_item(({"slope", "slopes", "boulder", "boulders"}), 
        "On the bare stony slopes frowned over by the cliffs, there " +
        "is no nook or hollow to shelter in. A few large boulders " +
        "are lying on the slopes, probably fallen down from the " +
        "precipe a long time ago.\n");
    add_item(({"path"}), 
        "There is no path here, but you can only go north or south.\n");
#ifndef RHOVANION_CLOSED
    add_exit(COMMON_DIR + "rholink1",    "northwest",     0, 5);
#else
    add_exit(COMMON_DIR + "shirelink2",  "northwest",     0, 5);
#endif
    add_exit(ITH_DIR + "dagorlad/path4", "southeast", 0, 5);
}

string
short_desc()
{
    if (areatype != 9)
        return ::short_desc();

    return "Barren "+areadesc+" in the "+area+" parts of "+areaname+" in "+land;
}

