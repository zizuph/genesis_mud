/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest42","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest43","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest34","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest25","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest24","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest23","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest32","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest41","northwest",0,FOREST_FATIGUE);
}
