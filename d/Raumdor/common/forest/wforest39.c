/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest53","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest54","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest40","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest30","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest29","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest28","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest38","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest52","northwest",0,FOREST_FATIGUE);
}

