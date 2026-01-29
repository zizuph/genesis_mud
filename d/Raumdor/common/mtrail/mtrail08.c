/* Mountain trail room, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    type = "east";
    roadWest = "west";
    roadEast = "southeast";
    ::create_room();
    set_long("You are at a turning point in the trail, leveling out " +
        "to the " + roadWest + " and descending to the " + roadEast +
        ". Below is an immense valley, a mixture of plains and hills. " +
        "You can barely make out what must be cities in the distance.\n");
    add_exit(MTRAIL_DIR + "mtrail07","west", 0, 2);
    add_exit(MTRAIL_DIR + "mtrail09", roadEast, "@@down", 2);
}
