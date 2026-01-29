/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest62","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest63","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest49","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest35","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest34","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest33","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest47","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest61","northwest",0,FOREST_FATIGUE);
}

