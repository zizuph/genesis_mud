/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest31","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest32","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest20","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest08","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest07","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest06","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest18","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest30","northwest",0,FOREST_FATIGUE);
}

