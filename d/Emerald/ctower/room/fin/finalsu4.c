#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_item(({"stair", "stairs", "stairway"}),  "This "+
     "stairway appears to be quite sturdy even though"+
     " there doesn't seem to be any visible support.\n" );
 
  add_exit(CTOWER_ROOM_FIN + "central2", "northwest");
  add_exit(CTOWER_ROOM_FIN + "finalsd4", "up");
}
