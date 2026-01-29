/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest67","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest68","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest54","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest40","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest39","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest38","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest52","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest66","northwest",0,FOREST_FATIGUE);
}

