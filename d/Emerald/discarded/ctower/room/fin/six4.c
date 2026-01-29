#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "done1", "north");
  add_exit(CTOWER_ROOM_FIN + "finalsd3", "west");
  add_exit(CTOWER_ROOM_FIN + "finalsd4", "east");
}
