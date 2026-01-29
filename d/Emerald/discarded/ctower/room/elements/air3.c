#include "../../ctower.h"

inherit AIRSTD;
 
void
create_air()
{
  add_exit(CTOWER_ROOM_ELEM + "air5", "southeast");
  add_exit(CTOWER_ROOM_ELEM + "airsd", "northwest");
}
