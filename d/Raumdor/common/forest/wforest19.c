/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest29","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest30","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest20","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest10","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest09","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest08","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest18","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest28","northwest",0,FOREST_FATIGUE);
}

