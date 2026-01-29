#include "../../ctower.h"

inherit EARTHSTD;
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "earth6", "southeast");
  add_exit(CTOWER_ROOM_ELEM + "earth2", "northwest");
}
