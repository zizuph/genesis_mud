/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    set_long("@@road_long@@To the west is a stream and bridge.\n");
    add_exit(FOREST_DIR + "nforest05","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest06","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest86","east");
    add_exit(FOREST_DIR + "wforest72","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest71","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest70","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","west");
    add_exit(FOREST_DIR + "nforest04","northwest",0,FOREST_FATIGUE);
}
