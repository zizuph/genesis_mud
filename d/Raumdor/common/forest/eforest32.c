/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest41","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest42","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest33","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest24","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest23","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest22","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest31","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest40","northwest",0,FOREST_FATIGUE);
}
