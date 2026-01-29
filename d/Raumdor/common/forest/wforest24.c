/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest34","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest35","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest25","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest15","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest14","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest13","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest23","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest33","northwest",0,FOREST_FATIGUE);
}

