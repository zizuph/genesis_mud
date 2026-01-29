#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem6", "north");
  add_exit(CTOWER_ROOM_ELEM + "fire1", "east");
  add_exit(CTOWER_ROOM_ELEM + "elem1", "southeast");
}
