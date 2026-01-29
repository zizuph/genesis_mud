/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    roadEast = "northeast";
    roadWest = "southwest";
    ::create_room();
    add_exit(FOREST_DIR + "wforest81","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest82","northeast");
    add_exit(FOREST_DIR + "wforest68","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest54","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest53","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest52","southwest");
    add_exit(FOREST_DIR + "wforest66","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest80","northwest",0,FOREST_FATIGUE);
}
