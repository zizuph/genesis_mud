/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest33","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest34","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest24","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest14","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest13","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest22","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest32","northwest",0,FOREST_FATIGUE);
}

