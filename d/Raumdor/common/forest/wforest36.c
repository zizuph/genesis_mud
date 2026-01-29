/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest50","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest51","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest37","east");
    add_exit(FOREST_DIR + "wforest27","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest26","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest25","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest35","west");
    add_exit(FOREST_DIR + "wforest49","northwest",0,FOREST_FATIGUE);
}
