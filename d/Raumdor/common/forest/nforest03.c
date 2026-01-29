/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    forest_details = " To the north you see what looks like a small pond.";
    ::create_room();
    add_item(({"pond"}),"You can't see much from here.\n");
    add_exit(FOREST_DIR + "nforest15","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest16","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest04","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest83","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest82","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest02","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest14","northwest",0,FOREST_FATIGUE);
}

