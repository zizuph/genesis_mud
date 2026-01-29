/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest75","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest76","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest62","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest48","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest47","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest46","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest60","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest74","northwest",0,FOREST_FATIGUE);
}

