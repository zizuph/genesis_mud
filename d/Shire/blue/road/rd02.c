/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "west of";
   areaname = "the Gulf of Lune";
   land = "the Shire";
   areatype = 1;
   areadesc = "field";
   grass = "green";

    extraline = "The field surrounds you obscuring your view of most " +
        "everything nearby. However, to the west, you catch a glint, " +
        "or sparkle, of water, which must surely be the Gulf of Lune. " +
        "The path runs north and south.";
   
    add_item(({"tall grass"}),
        "It is tall and green. It hides the ground and waves lazily in " +
        "the breeze.\n");
    add_item(({"path", "road"}),
        "The path runs through the field, almost hidden by the long grass.\n");
    add_item(({"gulf of lune", "gulf of lhun", "lune", "lhun"}),
        "The Gulf of Lune sparkles in the distance, like a thin, blue " +
        "ribbon. It is rumoured the gulf was formed long ago when the " +
        "world was remade and that that elves still live near it, some " +
        "leaving forever, never to be seen.\n");

   add_exit(ROAD_DIR + "rd03","north");
   add_exit(ROAD_DIR + "rd01","south");
}
