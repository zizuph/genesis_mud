/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest35","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest36","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest24","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest12","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest11","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest10","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest22","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest34","northwest",0,FOREST_FATIGUE);
}

