/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest25","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest26","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest16","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest06","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest05","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest04","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest14","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest24","northwest",0,FOREST_FATIGUE);
}

