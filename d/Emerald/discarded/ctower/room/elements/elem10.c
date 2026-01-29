#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem8", "southwest");
  add_exit(CTOWER_ROOM_ELEM + "earth1", "south");
  add_exit(CTOWER_ROOM_ELEM + "elem11", "east");
}
