#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem12", "northwest");
  add_exit(CTOWER_ROOM_ELEM + "elem7", "south");
  add_exit(CTOWER_ROOM_ELEM + "water1", "west");
}
