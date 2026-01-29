/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    roadEast = "northeast";
    ::create_room();
    add_exit(FOREST_DIR + "nforest11","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest12","northeast");
    add_exit(FOREST_DIR + "eforest43","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest34","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest33","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest32","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest41","west");
    add_exit(FOREST_DIR + "nforest10","northwest",0,FOREST_FATIGUE);
}
