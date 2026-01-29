#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin12", "east");
  add_exit(CTOWER_ROOM_FIN + "fin10", "west");
}
