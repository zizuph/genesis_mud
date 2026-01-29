/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest76","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest77","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest63","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest49","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest48","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest47","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest61","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest75","northwest",0,FOREST_FATIGUE);
}

