/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest42","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest43","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest32","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest20","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest19","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest18","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest30","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest41","northwest",0,FOREST_FATIGUE);
}

