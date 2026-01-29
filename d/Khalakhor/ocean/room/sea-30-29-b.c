#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-b";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(BAILE_ASHLAGH_LANDING, "north", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the coast of Baile Ashlagh, and you notice something "+
           "that resembles a pier to the north. That might be a good landing "+
           "spot!\n");
}
