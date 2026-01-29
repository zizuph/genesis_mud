/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest23","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest24","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest16","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest08","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest07","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest06","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest14","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest22","northwest",0,FOREST_FATIGUE);
}
