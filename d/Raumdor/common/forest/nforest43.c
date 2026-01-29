/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest52","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest53","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest44","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest33","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest32","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest31","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest42","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest51","northwest",0,FOREST_FATIGUE);
}

