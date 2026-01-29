/* Mountain trail room, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

void
create_room()
{
    type = "east";
    roadWest = "west";
    roadEast = "east";
    ::create_room();
    add_exit(MTRAIL_DIR + "mtrail16", roadWest, "@@up", 2);
    add_exit(MTRAIL_DIR + "mtrail18", roadEast, "@@down", 2);
}

