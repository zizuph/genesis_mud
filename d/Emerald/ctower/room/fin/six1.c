#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_item(({"wall", "floor", "ceiling"}),  "The walls are "+
     "made of a dark crystal that seems to absorb the light.\n" );
 
  add_exit(CTOWER_ROOM_FIN + "done1", "south");
  add_exit(CTOWER_ROOM_FIN + "finalsd2", "east");
  add_exit(CTOWER_ROOM_FIN + "finalsd1", "west");
}
