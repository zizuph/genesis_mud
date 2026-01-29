/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest33","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest34","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest22","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest10","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest09","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest08","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest20","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest32","northwest",0,FOREST_FATIGUE);
}

