/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest85","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest86","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest72","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest58","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest57","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest56","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest70","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest84","northwest",0,FOREST_FATIGUE);
}

