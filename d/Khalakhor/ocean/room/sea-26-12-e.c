#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-e";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(HAMMERHANDS_LANDING, "south", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the rocky shore of the southwestern speir next to you. "+
           "Past the rocks, a wide steppe opens to the south, and a chain of "+
           "extremelly tall mountains comes very close to the shore. It "+
           "looks like a gap between the rocks has been made, allowing you "+
           "to make a landfall to the south.\n");
}
