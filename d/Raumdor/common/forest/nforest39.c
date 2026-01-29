/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest48","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest49","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest40","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest29","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest28","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest27","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest38","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest47","northwest",0,FOREST_FATIGUE);
}

