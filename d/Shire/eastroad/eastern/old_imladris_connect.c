/*
 * Connection between Imladris and
 * Great East Road
 * Finwe, August 1998
 */
#pragma save_binary
#pragma strict_types
 
#include "local.h"
 
inherit EAST_ROAD;

#define TROLLSHAW_DIR   "/d/Shire/common/trollsh/"
#define RIVER_DIR      "/d/Shire/rivendell/room/river/"
 
void
create_er_room()
{
    set_area("at a crossroad on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("foothill");
    set_grass("wet, long");
    set_treetype("oak");
 
    set_extraline("The Great East Road ends here.  It " +
        "connects to a path that winds into the Misty " +
        "Mountains.");

  
    add_item(({"forest","oak forest","trees"}),
      "The shadow of Misty Mountains envelopes the Great East "+
      "Road here. Ancient oaks look ominous and gloomy as they " + 
      "rise up along the road.\n");
    add_item(({"mountains", "misty mountains", "foothills"}),
      "The tops of the Misty Mountains rise up before you. " +
      "They look forbidding and dangerous as they stand in " +
      "the distance.\n");
    add_item(({"path", "paths"}),
        "One path looks well used as it heads into the " +
        "mountains, skirting the river to the east. Another " +
        "less travelled path runs east to the river.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows east out of the mountains and south " +
        "alongside the road.\n");
 
    add_exit(TROLLSHAW_DIR + "mpath6",    "north", 0, 1);
    add_exit(TROLLSHAW_DIR + "mpath4",    "south", 0, 1);
add_exit(RIVER_DIR    + "riverbank", "east", 0, 2,1);

/*
    add_exit(RIVER_DIR    + "riverbank", "east", "@@no_way@@",2,1);
*/
}


int
no_way()
{
   if (this_player()->query_wiz_level())
        return 0;
    write("You can't go there. It seems the river has flooded " +
        "its banks, making it impossible to go there.\n");
    return 1;
}
