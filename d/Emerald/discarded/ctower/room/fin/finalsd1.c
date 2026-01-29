#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_item(({"stair", "stairs", "stairway"}),  "This "+
     "stairway appears to be quite sturdy even though"+
     " there doesn't seem to be any visible support.\n" );
 
  add_exit(CTOWER_ROOM_FIN + "finalsu1", "down");
  add_exit(CTOWER_ROOM_FIN + "six2", "south");
  add_exit(CTOWER_ROOM_FIN + "six1", "east");
}
