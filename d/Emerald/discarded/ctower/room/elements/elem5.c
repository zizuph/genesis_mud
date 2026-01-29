#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem7", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem3", "southwest");
  add_exit(CTOWER_ROOM_ELEM + "air1", "west");
}
