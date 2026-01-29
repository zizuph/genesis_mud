/* East Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit EFOREST_ROOM;

void
create_room()
{
    ::create_room();
    add_exit(FOREST_DIR + "eforest38","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest39","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest30","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest21","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "eforest20","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest58","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest72","west",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest86","northwest",0,FOREST_FATIGUE);
}
