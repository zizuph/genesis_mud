#include "../../ctower.h"

inherit EARTHSTD;
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "earth5", "northwest");
  add_exit(CTOWER_ROOM_ELEM + "earth9", "southeast");
}
