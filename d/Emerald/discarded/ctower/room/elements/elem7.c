#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem9", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem5", "south");
  add_exit(CTOWER_ROOM_ELEM + "trial2", "east");
}
