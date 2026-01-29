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
          +  "there is only one window far to the south. The hallway runs "
          +  "north and south.", SL));

    add_exit(PALACE + "office8","east",0,0);
    add_exit(PALACE + "office4","west",0,0);
    add_exit(PALACE + "hall5","north",0,0);
    add_exit(PALACE + "hall3","south",0,0);
}

