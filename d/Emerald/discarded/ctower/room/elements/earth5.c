#include "../../ctower.h"

inherit EARTHSTD;
 
void
create_earth()
{
  add_exit(CTOWER_ROOM_ELEM + "earth3", "northeast");
  add_exit(CTOWER_ROOM_ELEM + "earth7", "southeast");
}
