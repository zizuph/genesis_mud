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
    add_exit(FOREST_DIR + "wforest66","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest67","northeast");
    add_exit(FOREST_DIR + "wforest53","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest39","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest38","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest37","southwest");
    add_exit(FOREST_DIR + "wforest51","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest65","northwest",0,FOREST_FATIGUE);
}
