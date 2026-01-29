/* The roads of Raumdor, credit to Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    roadWest = "southwest";
    roadEast = "east";
    proximity = "drakmere";
    ::create_room();
    add_exit(ROAD_DIR + "road16","east",0,2);
    add_exit(ROAD_DIR + "road14","southwest",0,1);
}
