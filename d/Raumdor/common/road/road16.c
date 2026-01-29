/* The roads of Raumdor, credit to Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    roadWest = "west";
    roadEast = "east";
    proximity = "drakmere";
    ::create_room();
    add_exit(ROAD_DIR + "road17","east",0,2);
    add_exit(ROAD_DIR + "road15","west",0,1);
}
