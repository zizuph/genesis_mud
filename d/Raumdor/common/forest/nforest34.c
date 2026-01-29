/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest45","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest46","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest35","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest23","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest22","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest21","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest33","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest44","northwest",0,FOREST_FATIGUE);
}

