#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "air1", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem5", "northeast");
  add_exit(CTOWER_ROOM_ELEM + "elem2", "west");
}
