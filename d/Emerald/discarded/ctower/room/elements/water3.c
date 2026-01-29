#include "../../ctower.h"

inherit WATERSTD;
 
void
create_water()
{
  add_exit(CTOWER_ROOM_ELEM + "water2", "northeast");
  add_exit(CTOWER_ROOM_ELEM + "water5", "southeast");
}
