/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest22","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest23","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest13","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest03","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest02","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest01","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest11","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest21","northwest",0,FOREST_FATIGUE);
}
