/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(NFLATS_DIR + "nflats08","northwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest01","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest02","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest82","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest68","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest67","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest66","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest80","west",0,FOREST_FATIGUE);
}

