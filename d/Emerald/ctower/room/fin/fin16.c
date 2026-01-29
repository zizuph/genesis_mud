#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  add_exit(CTOWER_ROOM_FIN + "fin13", "northwest");
  add_exit(CTOWER_ROOM_FIN + "fin14", "northeast");
}
