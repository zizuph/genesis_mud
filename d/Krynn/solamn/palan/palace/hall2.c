/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{
    set_short("Hallway");
    set_long(BS("It's an ordinary hallway which is a little dark since "
          +  "there is only one window far to the south. On the east "
          +  "doorway, a sign says '10'. The hallway runs "
          +  "north and south.", SL));

    add_exit(PALACE + "office10","east",0,0);
    add_exit(PALACE + "office2","west",0,0);
    add_exit(PALACE + "hall3","north",0,0);
    add_exit(PALACE + "hall1","south",0,0);
}
