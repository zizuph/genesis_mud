#include "../../ctower.h"

inherit FIRESTD;
 
void
create_fire()
{
  add_exit(CTOWER_ROOM_ELEM + "water5", "south");
}
 
int
query_transform()
{
  return 1;
}
