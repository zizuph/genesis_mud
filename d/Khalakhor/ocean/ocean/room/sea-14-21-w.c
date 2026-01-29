/*
 * Sa Morgan landing
 * Tapakah, 11/2021
 */

#include "../defs.h"

inherit KHALAKHOR_SEA + "sea-w";

void
create_sea_room ()
{
  ::create_sea_room();
  add_row_exits(SAMORGAN_LANDING, "north", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the rocky shore of the southwestern speir next to you. "+
           "To the north you see the village of Sa Morgan, and something that "+
           "looks like an harbor with a few piers. You will likely be able "+
           "to use one of them for landing.\n");
}
