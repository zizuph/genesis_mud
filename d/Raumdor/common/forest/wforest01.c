/* West Forest Room, Sarr */
/* 2017-06-28 Malus: Use new standard and adapt description to fit. */
#include "defs.h"
inherit WFOREST_ROOM;

void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " The trees give way to a bleak and narrow coast, " +
        "cold waters blocking further travel. From this vantage point, you " +
        "can see the gulf curve southeast and the forest dissipate into " +
        "open terrain further south.";
    ::create_room();
    add_item(({"coast"}), "Cold and rocky, it is not suitable for travel " +
            "by foot.\n");
    add_item(({"waters","gulf"}), 
            "The sea gently rolls in the wind.\n");
    add_item(({"open terrain","flats"}),
            "The flats extend south into the mountains. They look barren.\n");
    add_item(({"mountains"}), "Mountains rises from the flats far to the " +
            "south.\n");
    set_no_exit_msg(({"northwest","west","south","southwest"}),
            "Cold waters dissuade you from proceeding that way.\n");
    add_exit(FOREST_DIR + "wforest11","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest02","east",0,FOREST_FATIGUE);
    add_exit(SFLATS_DIR + "sflats01","southeast",0,FOREST_FATIGUE);
}

