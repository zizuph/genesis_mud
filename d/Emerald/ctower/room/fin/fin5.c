#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin2", "north");
  add_exit(CTOWER_ROOM_FIN + "fin1", "northwest");
  add_exit(CTOWER_ROOM_FIN + "fin3", "northeast");
}
