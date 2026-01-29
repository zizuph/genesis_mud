#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem8", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem4", "south");
  add_exit(CTOWER_ROOM_ELEM + "trial1", "west");
}
