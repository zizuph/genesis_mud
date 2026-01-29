/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest17","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest18","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest06","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest86","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest85","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest04","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest16","northwest",0,FOREST_FATIGUE);
}

