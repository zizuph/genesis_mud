/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest32","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest33","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest21","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest09","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest08","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest07","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest19","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest31","northwest",0,FOREST_FATIGUE);
}

