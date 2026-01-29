#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin16", "southeast");
  add_exit(CTOWER_ROOM_FIN + "fin9", "northeast");
}
