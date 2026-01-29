/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest74","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest75","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest61","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest47","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest46","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest45","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest59","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest73","northwest",0,FOREST_FATIGUE);
}

