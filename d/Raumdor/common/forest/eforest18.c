/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest26","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest27","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest19","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest11","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest10","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest09","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest17","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest25","northwest",0,FOREST_FATIGUE);
}
