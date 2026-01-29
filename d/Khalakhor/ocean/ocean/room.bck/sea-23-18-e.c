/*
 * Port Macdunn landing
 * Tapakah, 11/2021
 */

#include "../defs.h"

inherit KHALAKHOR_SEA + "sea-e";

void
create_sea_room ()
{
  ::create_sea_room();
  add_row_exits(PORTMACDUNN_LANDING, "east", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You are next to the harbor of Port Macdunn. Being the biggest "+
           "port in this area of Khalakhor, it provides docking facilities "+
           "to the visiting vessels. You notice an available pier at your "+
           "east.\n");
}
