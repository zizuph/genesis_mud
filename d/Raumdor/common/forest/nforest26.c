/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(NFLATS_DIR + "nflats23","northwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest37","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest38","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest27","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest14","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest13","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest25","west",0,FOREST_FATIGUE);
}

