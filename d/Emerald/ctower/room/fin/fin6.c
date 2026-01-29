#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin10", "southwest");
  add_exit(CTOWER_ROOM_FIN + "fin3", "northwest");
}
