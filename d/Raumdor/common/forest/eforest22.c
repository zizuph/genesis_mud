/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest31","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest32","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest23","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest15","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest14","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest13","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest21","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest30","northwest",0,FOREST_FATIGUE);
}
