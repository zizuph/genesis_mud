/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest32","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest33","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest23","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest13","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest11","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest21","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest31","northwest",0,FOREST_FATIGUE);
}

