/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest79","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest80","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest66","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest52","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest51","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest50","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest64","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest78","northwest",0,FOREST_FATIGUE);
}

