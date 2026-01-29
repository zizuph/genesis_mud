/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest64","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest65","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest51","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest37","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest36","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest35","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest49","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest63","northwest",0,FOREST_FATIGUE);
}

