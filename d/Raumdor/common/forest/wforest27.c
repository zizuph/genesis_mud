/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest37","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest38","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest28","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest18","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest17","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest16","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest26","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest36","northwest",0,FOREST_FATIGUE);
}

