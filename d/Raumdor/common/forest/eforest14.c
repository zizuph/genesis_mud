/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest22","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest23","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest15","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest07","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest06","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest05","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest13","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest21","northwest",0,FOREST_FATIGUE);
}
