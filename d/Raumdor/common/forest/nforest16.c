/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    forest_details = " To the west you see what looks like a small pond.";
    ::create_room();
    add_item(({"pond"}),"You can't see much from here.\n");
    add_exit(FOREST_DIR + "nforest28","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest29","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest17","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest05","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest04","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest03","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest27","northwest",0,FOREST_FATIGUE);
}

