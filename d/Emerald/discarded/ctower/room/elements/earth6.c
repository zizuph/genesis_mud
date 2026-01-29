#include "../../ctower.h"

inherit EARTHSTD;
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "earth8", "southwest");
  add_exit(CTOWER_ROOM_ELEM + "earth4", "northwest");
}
