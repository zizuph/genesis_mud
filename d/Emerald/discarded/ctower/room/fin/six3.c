#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "done1", "west");
  add_exit(CTOWER_ROOM_FIN + "finalsd4", "south");
  add_exit(CTOWER_ROOM_FIN + "finalsd2", "north");
}
