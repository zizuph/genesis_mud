/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest46","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest36","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest24","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest23","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest22","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest34","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest45","northwest",0,FOREST_FATIGUE);
}

