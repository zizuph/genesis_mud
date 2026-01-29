/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    roadWest = "southwest";
    roadEast = "northeast";
    ::create_room();
    add_exit(FOREST_DIR + "nforest24","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest50","northeast");
    add_exit(FOREST_DIR + "eforest47","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest44","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest43","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest42","southwest");
    add_exit(FOREST_DIR + "nforest11","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest23","northwest",0,FOREST_FATIGUE);
}
