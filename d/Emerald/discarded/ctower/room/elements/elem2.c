#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM + "trialsd", "south");
  add_exit(CTOWER_ROOM_ELEM + "elem3", "east");
  add_exit(CTOWER_ROOM_ELEM + "elem1", "west");
}
