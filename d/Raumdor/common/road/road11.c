/* The roads of Raumdor, credit to Sarr */
#include "defs.h"
inherit ROAD_ROOM;

void
create_room()
{
    roadWest = "southwest";
    roadEast = "northeast";
    proximity = "drakmere";
    longSuffix = " A small path leads to some old ruins to the northwest.\n";
    ::create_room();
    add_item(({"ruins", "old ruins"}), "Blocks of old stone, many broken " +
            "and scattered, lie to the northwest.\n");
    add_exit(ROAD_DIR + "road12","northeast",0,2);
    add_exit(ROAD_DIR + "road10","southwest",0,1);
    add_exit(PLAINS_DIR + "beastruin1","northwest",0,1);
}
