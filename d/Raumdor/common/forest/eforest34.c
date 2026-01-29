/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest43","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest44","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest35","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest26","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest25","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest24","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest33","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest42","northwest",0,FOREST_FATIGUE);
}
