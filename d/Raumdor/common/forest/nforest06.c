/* North Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit NFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "nforest18","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest19","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest07","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest38","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest86","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest85","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest05","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest17","northwest",0,FOREST_FATIGUE);
}

