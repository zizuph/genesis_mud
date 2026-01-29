/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    forest_details = " To the east you see what looks like a small pond.";
    ::create_room();
    add_item(({"pond"}),"You can't see much from here.\n");
    add_exit(FOREST_DIR + "nforest26","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest27","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest03","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest02","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest01","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest13","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest25","northwest",0,FOREST_FATIGUE);
}

