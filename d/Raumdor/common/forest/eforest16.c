/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest24","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest25","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest17","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest09","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest08","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest07","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest15","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest23","northwest",0,FOREST_FATIGUE);
}
