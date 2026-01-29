#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin4", "northwest");
  add_exit(CTOWER_ROOM_FIN + "fin13", "southwest");
  add_exit(CTOWER_ROOM_FIN + "fin8", "west");
}
