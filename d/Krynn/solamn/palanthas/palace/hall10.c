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
          +  "there is only one window very far to the south. On the east "
          +  "doorway, a sign says '17'. The west "
          +  "doorway is marked '15'. The hallway continues "
          +  "south, whereas the label to the north reads '16'.\n");

    add_exit(PALACE + "office17","east",0,0);
    add_exit(PALACE + "office15","west",0,0);
    add_exit(PALACE + "office16","north",0,0);
    add_exit(PALACE + "hall9","south",0,0);
}
