/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest53","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest54","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest45","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest34","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest33","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest32","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest43","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest52","northwest",0,FOREST_FATIGUE);
}

