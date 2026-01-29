/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    forest_details = " To the southwest you see what looks like a " +
        "small pond.";
    ::create_room();
    add_item(({"pond"}),"You can't see much from here.\n");
    add_exit(FOREST_DIR + "nforest39","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest40","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest29","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest17","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest16","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest27","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest38","northwest",0,FOREST_FATIGUE);
}

