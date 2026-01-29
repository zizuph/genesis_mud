/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "south";
}

void
create_room()
{
    set_short("Hallway");
    set_long("It's an ordinary hallway which is a little dark since "
          +  "there is only one window far to the south. On the east "
          +  "doorway, a sign says '19'. The west doorway is "
          +  "marked '13'. The hallway runs "
          +  "north and south.\n");

    add_exit(PALACE + "office19","east",0,0);
    add_exit(PALACE + "office13","west",0,0);
    add_exit(PALACE + "hall9","north",0,0);
    add_exit(PALACE + "hall7","south",0,0);
}

 
