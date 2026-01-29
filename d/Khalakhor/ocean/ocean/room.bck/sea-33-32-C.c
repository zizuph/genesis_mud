/*
 * Khalakhor - Sparkle connection point
 * Tapakah, 11/2021
 */

#include "../defs.h"

inherit KHALAKHOR_SEA + "sea-C";

void
create_sea_room ()
{
  ::create_sea_room();
  add_row_exits(SPARKLE_CONNECTION, "southeast", 0, 1);

  reset_sea_room();

  add_item(({"southeast", "current"}),
           "This current seems to have a very strong flow as if moving "+
           "the water between two very different destinations.\n");

  set_long(long() + "A rather strong current is driving the water to the "+
           "southeast. The current seems somewhat unnatural but not too "+
           "dangerous at the same time.\n");
  set_sailing_difficulty(ROUGH_SEAS_DIFFICULTY);
}
