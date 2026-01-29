#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-n";

void
create_sea_room ()
{
  ::create_sea_room();
  add_row_exits(WASTELANDS_LANDING, "south", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "Suddenly you notice a flat area of sturdy stone protruding "+
           "slightly into the ocean from between the jagged rocks of the "+
           "coastline. You might be able to make the landfall there.\n");
}
