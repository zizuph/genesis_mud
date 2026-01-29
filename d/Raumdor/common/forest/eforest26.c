/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest35","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest36","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest27","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest19","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest18","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest17","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest25","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest34","northwest",0,FOREST_FATIGUE);
}
