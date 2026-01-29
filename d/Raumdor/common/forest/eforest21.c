/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest30","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest31","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest22","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest14","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest13","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest12","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest20","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest29","northwest",0,FOREST_FATIGUE);
}
