/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest38","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest39","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest28","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest16","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest15","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest14","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest26","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest37","northwest",0,FOREST_FATIGUE);
}

