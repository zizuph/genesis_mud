/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest14","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest03","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest83","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest82","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest81","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest01","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest13","northwest",0,FOREST_FATIGUE);
}

