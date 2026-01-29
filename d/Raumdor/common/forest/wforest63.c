/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest77","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest78","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest64","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest50","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest49","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest48","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest62","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest76","northwest",0,FOREST_FATIGUE);
}

