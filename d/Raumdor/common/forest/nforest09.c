/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest21","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest22","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest10","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest41","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest40","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest39","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest08","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest20","northwest",0,FOREST_FATIGUE);
}

