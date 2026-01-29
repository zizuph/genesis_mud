/* West Forest Room, Sarr */
#include "defs.h"
inherit WFOREST_ROOM;
inherit COMMON_LIB_DIR + "carvings";

void
create_room()
{
    forest_intro = "You are near the fringes of a dark forest.";
    forest_features = " To the west the trees run up against a stone wall.";
    ::create_room();
    add_item("wall", "The wall runs from the south and turns to the " +
      "northwest. It is made of smooth stone blocks. Looking closely, " +
      "you can see subtle carvings all over the surface.\n");
    add_item(({"blocks", "stone blocks"}),
      "The stone blocks are in good condition for being amidst the forest. " +
      "Although easy to miss on first glance, they are covered in carvings.\n");
    add_item("carvings", "@@carvings_description@@");
    add_cmd_item(({"wall", "stone wall"}), "climb",
        "It is too tall and smooth to climb.\n");
    set_no_exit_msg(({"northwest","west","southwest"}),
            "The stone wall blocks you.\n");
    set_no_exit_msg("southwest",
            "Cold waters dissuade you from proceeding that way.\n");
    add_exit(FOREST_DIR + "wforest31","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest22","east",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest32","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest11","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest12","southeast",0,FOREST_FATIGUE);
}

