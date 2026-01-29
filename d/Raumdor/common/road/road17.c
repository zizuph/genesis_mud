/* The roads of Raumdor, credit to Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    roadWest = "west";
    roadEast = "east";
    proximity = "drakmere";
    longSuffix = " The gatehouse is within view.\n";
    ::create_room();
    add_item("gatehouse","It is sizable, arching over a large gates.\n");
    add_exit(DRAKMERE_DIR + "wgate","east",0,1);
    add_exit(ROAD_DIR + "road16","west",0,1);
}
