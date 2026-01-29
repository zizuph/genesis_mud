/* The road through the forest of Raumdor, by Sarr */
/* 2017-06-26 Malus: Spawn fix and standardization */ 
#include "defs.h"
inherit FOREST_ROAD_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest09","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest10","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest41","east");
    add_exit(FOREST_DIR + "eforest32","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest31","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest30","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest39","west");
    add_exit(FOREST_DIR + "nforest08","northwest",0,FOREST_FATIGUE);

}
