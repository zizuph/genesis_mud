#include "../defs.h"
#include <stdproperties.h>

inherit KHALAKHOR_SEA + "sea-w";

void
create_sea_room()
{
  ::create_sea_room();
  add_row_exits(DRUID_LANDING, "south", 0, 1);

  reset_sea_room();

  add_item(({"coast", "land"}),
           "You see the rocky shore of the southwestern speir next to you. "+
           "Past the rocks, a dark-green broadleaf forest looms in the east. "+
           "You notice a gap where the rocks have been cleaned, whether "+
           "by nature, or by living things, producing a clearing where "+
           "you can make landfall.\n");
}
