/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest44","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest45","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest36","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest27","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest26","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest25","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest34","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest43","northwest",0,FOREST_FATIGUE);
}
