/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "wforest23","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest24","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest14","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest04","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest03","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest02","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest22","northwest",0,FOREST_FATIGUE);
}
