/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

object baker;

string
query_to_jail()
{
  return "east";
}

void
reset_palan_room()
{
    if (baker)
      return;
    baker = clone_object(LIV + "baker");
    baker->move(TO);
}

void
create_palan_room()
{

    set_short("Northwestern part of Palanthas");
    set_long(BS("You are on Circle Street in the northwestern "
        +    "part of Palanthas. This is more of a "
        +    "merchandise area, so you find a shop to the "
        +    "north and some kind of bakery to the west. From "
	+    "the east, a light wind blows the smell of "
        +   "salty water down the street and you can even get a "
        +    "glimpse of water looking east.",SL));

    add_exit(ROOM + "street16","east",0,1);
    add_exit(ROOM + "pastry","west",0,1);
    add_exit(ROOM + "street9","southwest","@@bend_south",1);
    add_exit(ROOM + "shop","north",0,1);

    reset_room();
}

int
bend_south()
{
  write("The street bends to the south.\n");
  return 0;
}
