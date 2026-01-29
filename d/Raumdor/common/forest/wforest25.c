/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest35","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest36","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest26","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest16","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest15","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest14","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest24","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest34","northwest",0,FOREST_FATIGUE);
}

