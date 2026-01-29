/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest27","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest28","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest18","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest08","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest07","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest06","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest16","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest26","northwest",0,FOREST_FATIGUE);
}

