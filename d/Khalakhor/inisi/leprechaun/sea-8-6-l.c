#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-l";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(LUCKY_LANDING, "north", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "Finally, you seem to have encountered a break in the green wall "+
           "surrounding the island. You notice a small but sturdy pier to "+
           "your north where you can make your landfall.\n";
}
