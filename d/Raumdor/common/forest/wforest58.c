/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest72","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest29","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest20","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest12","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest44","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest43","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest57","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest71","northwest",0,FOREST_FATIGUE);
}

