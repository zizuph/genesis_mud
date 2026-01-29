#include "../../ctower.h"

inherit EARTHSTD;
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "earth9", "southwest");
  add_exit(CTOWER_ROOM_ELEM + "earth6", "northeast");
}
