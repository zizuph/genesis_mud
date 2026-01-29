/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest48","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest49","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest46","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest37","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest36","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest35","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest44","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest47","northwest",0,FOREST_FATIGUE);
}
