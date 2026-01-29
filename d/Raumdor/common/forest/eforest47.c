/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest50","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest51","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest48","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest45","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest44","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest43","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest12","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest24","northwest",0,FOREST_FATIGUE);
}
