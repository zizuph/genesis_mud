#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

create_kalaman_room()
{
  set_short("Poor district");
  set_long("You stand in a soon to be poor district of Kalaman.\n");

  add_exit("s03","west",0);
  add_exit("s04", "north" ,0);
  add_exit("s01", "south",0);
  add_exit("s05", "east",0);
}
