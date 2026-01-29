/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest49","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest50","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest36","east");
    add_exit(FOREST_DIR + "wforest26","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest25","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest24","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest34","west");
    add_exit(FOREST_DIR + "wforest48","northwest",0,FOREST_FATIGUE);
}
