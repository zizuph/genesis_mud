#include "../../ctower.h"

inherit ELEMSTD;
 
void
create_element()
{
  add_exit(CTOWER_ROOM_ELEM + "elem10", "west");
  add_exit(CTOWER_ROOM + "trialsu", "north");
  add_exit(CTOWER_ROOM_ELEM + "elem12", "east");
}
