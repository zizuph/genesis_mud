/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    roadWest = "southwest";
    ::create_room();
    add_exit(FOREST_DIR + "nforest02","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest03","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest83","east");
    add_exit(FOREST_DIR + "wforest69","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest68","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest67","southwest");
    add_exit(FOREST_DIR + "wforest81","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest01","northwest",0,FOREST_FATIGUE);
}
