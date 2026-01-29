/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest65","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest66","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest52","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest38","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest37","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest36","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest50","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest64","northwest",0,FOREST_FATIGUE);
}

