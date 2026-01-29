#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem10", "northeast");
  add_exit(CTOWER_ROOM_ELEM + "elem6", "south");
  add_exit(CTOWER_ROOM_ELEM + "earth1", "east");
}
