/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest78","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest79","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest65","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest51","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest50","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest49","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest63","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest77","northwest",0,FOREST_FATIGUE);
}

