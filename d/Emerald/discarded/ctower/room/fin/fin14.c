#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin18", "southeast");
  add_exit(CTOWER_ROOM_FIN + "fin16", "southwest");
  add_exit(CTOWER_ROOM_FIN + "fin17", "south");
}
