/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "north of";
   areaname = "the Great East Road";
   land = "the Shire";
   areatype = 1;
   areadesc = "field";
   grass = "green";

   extraline = "The field spreads out to the north. It is full of tall " +
   "grass waving in the breeze. There is a path in the grass running " +
   "north and south.";
   
   add_item(({"tall grass"}),
   "It is tall and green. It hides the ground and waves lazily in " +
   "the breeze.\n");

   add_item(({"path", "road"}),
   "The path runs through the field, almost hidden by the long grass.\n");


   add_exit(ROAD_DIR + "rd02","north");
   add_exit(GER_DIR  + "er2n","south");
}
