/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest24","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest25","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest15","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest05","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest04","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest03","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest13","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest23","northwest",0,FOREST_FATIGUE);
}

