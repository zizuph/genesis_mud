/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest12","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest47","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest44","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest35","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest34","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest33","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest42","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest11","northwest",0,FOREST_FATIGUE);
}
