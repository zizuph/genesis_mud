#include "../../ctower.h"

inherit EARTHSTD;
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "earth2", "northeast");
  add_exit(CTOWER_ROOM_ELEM + "earth5", "southwest");
}
