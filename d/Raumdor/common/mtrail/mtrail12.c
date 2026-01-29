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
    add_exit(MTRAIL_DIR + "mtrail11", roadWest, "@@up", 2);
    add_exit(MTRAIL_DIR + "mtrail13", roadEast, "@@down", 2);
}
