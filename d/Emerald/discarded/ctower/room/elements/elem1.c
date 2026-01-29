#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "fire1", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem2", "east");
  add_exit(CTOWER_ROOM_ELEM + "elem4", "northwest");
}
