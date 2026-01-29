/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest43","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest44","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest33","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest21","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest20","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest19","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest31","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest42","northwest",0,FOREST_FATIGUE);
}

