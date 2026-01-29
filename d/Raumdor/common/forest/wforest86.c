/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest06","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest07","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest38","east");
    add_exit(FOREST_DIR + "eforest29","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest72","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest71","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest85","west");
    add_exit(FOREST_DIR + "nforest05","northwest",0,FOREST_FATIGUE);
}
