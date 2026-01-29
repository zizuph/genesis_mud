#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-r";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(CARISCA_LANDING, "east", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the coast of Carisca around you. To the east a small "+
           "clearing has been made in the forest, making it a very good "+
           "place for a landing.\n");
}
