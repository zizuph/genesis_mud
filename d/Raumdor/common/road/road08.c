/* The roads of Raumdor, credit to Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    roadWest = "northwest";
    roadEast = "southeast";
    ::create_room();
    add_exit(ROAD_DIR + "road07","northwest",0,2);
    add_exit(ROAD_DIR + "road09","southeast",0,1);
}
