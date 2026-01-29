/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_details = " To the northeast you see what looks like ruins.";
    ::create_room();
    add_item(({"ruins"}),"From here it looks like a circle of stones.\n");
    add_exit(FOREST_DIR + "wforest68","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest69","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest55","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest41","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest40","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest39","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest53","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest67","northwest",0,FOREST_FATIGUE);
}

