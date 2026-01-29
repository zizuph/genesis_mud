#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin5", "southeast");
  add_exit(CTOWER_ROOM_FIN + "fin4", "southwest");
}
