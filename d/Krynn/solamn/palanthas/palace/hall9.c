/* created by Aridor 09/14/93 */

#include "../local.h"

inherit CITY_ROOMBASE;

string
query_to_jail()
{
  return "south";
}

void
create_palan_room()
{
    set_short("Hallway");
    set_long("It's an ordinary hallway which is a little dark since "
          +  "there is only one window far to the south. On the east "
          +  "doorway, a sign says '18'. The hallway runs "
          +  "north and south.\n");


    add_exit(PALACE + "office18","east",0,0);
    add_exit(PALACE + "hall10","north",0,0);
    add_exit(PALACE + "hall8","south",0,0);
}

