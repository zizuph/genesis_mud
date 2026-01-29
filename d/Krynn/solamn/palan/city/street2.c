/* created by Aridor 06/19/93 */

#include "../local.h"

inherit STREET_BASE

string
query_to_jail()
{
  return "northwest";
}

void
create_palan_room()
{
    set_short("Crossing Streets");
    set_long(BS("You stand in the middle of the Circle "
        +    "Street where it crosses the Clerist Road. "
        +    "To the southeast you see the city gate "
        +    "leading out of the city and to the northwest"
        +    " seems to be the center of Palanthas.", 75));

    add_exit(ROOM + "street4","northwest",0,1);
    add_exit(ROOM + "street5","southeast",0,1);
    add_exit(ROOM + "street18","northeast","@@bend_north",1);
    add_exit(ROOM + "street1","southwest","@@bend_west",1);
}


int
bend_north()
{
  write("The street bends to the north.\n");
  return 0;
}

int
bend_west()
{
  write("The street bends to the west.\n");
  return 0;
}
