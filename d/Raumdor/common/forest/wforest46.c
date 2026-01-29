/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest60","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest61","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest47","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest33","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest32","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest31","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest45","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest59","northwest",0,FOREST_FATIGUE);
}

