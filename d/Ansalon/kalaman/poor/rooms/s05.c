#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

string long_descr();

create_kalaman_room()
{
  set_short("Poor district");
  set_long(long_descr);

  add_exit("s02","west",0);
  add_exit("h01a", "north", 0);
  add_exit("h02a", "east", 0);
}

string
long_descr()
{
  return "You stand in a side street in the poor district of Kalaman, " +
    "to the east and north you see the entrance to two of the common " +
    "houses that are for the families that live in the poor district. " +
    "Back to the west you see a street crossing.\n";
}
