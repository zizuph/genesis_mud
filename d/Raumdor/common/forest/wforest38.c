/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest52","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest53","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest39","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest29","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest28","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest27","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest37","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest51","northwest",0,FOREST_FATIGUE);
}

