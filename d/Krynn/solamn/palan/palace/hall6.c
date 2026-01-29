/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

string
query_to_jail()
{
  return "north";
}

void
create_palan_room()
{
    set_short("Hallway");
    set_long(BS("It's an ordinary hallway with "
          +  "a window to the south. On the west "
          +  "doorway, a sign says '11'. The hallway continues "
          +  "north, and there are stairs leading down.", SL));

    add_exit(PALACE + "hall7","north",0,0);
    add_exit(PALACE + "office11","west",0,0);
    add_exit(PALACE + "hall1","down",0,0);
}

 
