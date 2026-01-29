#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin9", "east");
  add_exit(CTOWER_ROOM_FIN + "fin7", "west");
}
