#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem11", "west");
  add_exit(CTOWER_ROOM_ELEM + "water1", "south");
  add_exit(CTOWER_ROOM_ELEM + "elem9", "southeast");
}
