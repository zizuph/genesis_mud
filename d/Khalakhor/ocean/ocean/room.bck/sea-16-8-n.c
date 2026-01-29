/*
 * Daenbraigh landing
 * Tapakah, 11/2021
 */

#include "../defs.h"

inherit KHALAKHOR_SEA + "sea-n";

void
create_sea_room ()
{
  ::create_sea_room();
  add_row_exits(DAENBRAIGH_LANDING, "east", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see two breakwaters stretching out from the shore in the "+
           "western direction, and a medium-sized earthen pier between them. "+
           "You should be able to make the landfall at this pier.\n");
  add_item(({"breakwater", "breakwaters"}), "You see two elongated stone "+
           "stretching from the shore to the west, one slightly to the "+
           "south, and another to the north, seemingly to prevent eddies "+
           "and other navigational surprised.\n");
}
