#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-c";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(CADU_LANDING, "west", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the coast of Cadu and the pier stretching out to the west "+
           "This would probably be an excellent place for a landfall.\n");
}
