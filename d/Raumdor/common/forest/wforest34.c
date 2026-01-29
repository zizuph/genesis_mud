/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest48","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest49","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest35","east");
    add_exit(FOREST_DIR + "wforest25","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest24","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest23","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest33","west");
    add_exit(FOREST_DIR + "wforest47","northwest",0,FOREST_FATIGUE);
}
