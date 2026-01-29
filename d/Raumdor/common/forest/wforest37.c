/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    roadEast = "northeast";
    ::create_room();
    add_exit(FOREST_DIR + "wforest51","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest52","northeast");
    add_exit(FOREST_DIR + "wforest38","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest28","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest27","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest26","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest36","west");
    add_exit(FOREST_DIR + "wforest50","northwest",0,FOREST_FATIGUE);
}
