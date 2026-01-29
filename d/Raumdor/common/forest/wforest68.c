/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_details = " To the east you see what looks like ruins.";
    ::create_room();
    add_item(({"ruins"}),"From here it looks like a circle of stones.\n");
    add_exit(FOREST_DIR + "wforest82","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest83","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest69","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest55","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest54","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest53","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest67","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest81","northwest",0,FOREST_FATIGUE);
}

