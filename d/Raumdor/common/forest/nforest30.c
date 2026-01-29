/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest41","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest42","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest31","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest19","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest18","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest17","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest29","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest40","northwest",0,FOREST_FATIGUE);
}

