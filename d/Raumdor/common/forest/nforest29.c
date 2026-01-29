/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest40","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest41","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest30","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest18","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest17","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest16","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest28","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest39","northwest",0,FOREST_FATIGUE);
}

