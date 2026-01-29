#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-r";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(GALAITH_LANDING, "east", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the rocky shore coast of Galaith around you. To the east "+
           "a small pier has been constructed where you can finally land.\n");
}
