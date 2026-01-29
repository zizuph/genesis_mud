#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin10", "northwest");
  add_exit(CTOWER_ROOM_FIN + "fin18", "southwest");
}
