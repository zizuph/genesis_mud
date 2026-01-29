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
    add_exit(FOREST_DIR + "eforest52","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest53","northeast");
    add_exit(FOREST_DIR + "eforest51","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest48","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest47","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest12","southwest");
    add_exit(FOREST_DIR + "nforest24","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest36","northwest",0,FOREST_FATIGUE);
}
