/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest56","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest57","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest50","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest41","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest40","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest39","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest48","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest55","northwest",0,FOREST_FATIGUE);
}

