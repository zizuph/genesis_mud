#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "done1", "east");
  add_exit(CTOWER_ROOM_FIN + "finalsd3", "south");
  add_exit(CTOWER_ROOM_FIN + "finalsd1", "north");
}
