/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest32","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest33","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest24","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest16","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest15","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest14","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest22","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest31","northwest",0,FOREST_FATIGUE);
}
