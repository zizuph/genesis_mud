/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest19","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest20","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest08","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest39","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest38","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest86","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest06","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest18","northwest",0,FOREST_FATIGUE);
}

