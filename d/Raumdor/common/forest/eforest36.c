/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest45","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest46","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest37","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest28","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest27","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest26","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest35","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest44","northwest",0,FOREST_FATIGUE);
}
