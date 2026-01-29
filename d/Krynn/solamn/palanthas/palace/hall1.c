/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;


string
query_to_jail()
{
  return "up";
}

void
create_palan_room()
{
    set_short("Hallway");
    set_long("It's an ordinary hallway with "
          +  "a window to the south. On the west "
          +  "doorway, a sign says '01'. The east "
          +  "seems to lead into the entrance hall of the palace. "
          +  "The hallway continues to the north and some stairs lead "
          +  "up.\n");

    add_exit(PALACE + "palace1","east",0,0);
    add_exit(PALACE + "office1","west",0,0);
    add_exit(PALACE + "hall6","up",0,0);
    add_exit(PALACE + "hall2","north");
}

