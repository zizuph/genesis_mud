/*
 * Mariner's berth 
 */

#include "../defs.h"

inherit AVENIR_SEA +"avenir_sea-d";

void
create_sea_room ()
{
  ::create_sea_room();
  add_row_exits(AVENIR_BERTH, "north", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the rocky shore coast of Galaith around you. To the east "+
           "a small pier has been constructed where you can finally land.\n");
}
