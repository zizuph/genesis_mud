/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest51","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest52","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest43","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest32","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest31","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest30","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest41","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest50","northwest",0,FOREST_FATIGUE);
}

