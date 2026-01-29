/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest40","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest41","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest32","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest23","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest22","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest21","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest30","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest39","northwest",0,FOREST_FATIGUE);
}
