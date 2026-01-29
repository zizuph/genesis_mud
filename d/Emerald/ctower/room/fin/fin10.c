#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin6", "northeast");
  add_exit(CTOWER_ROOM_FIN + "fin15", "southeast");
  add_exit(CTOWER_ROOM_FIN + "fin11", "east");
}
