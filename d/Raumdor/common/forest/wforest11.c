/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " To the west the trees give way to a bleak and " +
        "narrow coast, cold waters blocking further travel.";
    ::create_room();
    add_item(({"coast"}), "Cold and rocky, it is not suitable for travel " +
            "by foot.\n");
    add_item(({"waters","gulf"}), 
            "The sea gently rolls in the wind.\n");
    set_no_exit_msg(({"northwest","west","southwest"}),
            "Cold waters dissuade you from proceeding that way.\n");
    add_exit(FOREST_DIR + "wforest21","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest22","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest02","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest01","south",0,FOREST_FATIGUE);
}
