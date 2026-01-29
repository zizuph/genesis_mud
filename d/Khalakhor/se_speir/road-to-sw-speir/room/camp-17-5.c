/*
 * Camp room on the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_CAMP;

string
setup_long ()
{
  string my_desc = ::setup_long();
  my_desc += "From the north and the east the camp is bound by a wide rocky "+
    "path. Past the path you can see the mountain ridge coming close.\n";
  add_item("path", "A path goes north of the camp, between it and the "+
           "mountains, disappearing in the east towards the plains "+
           "surrounding Port Macdunn.\n");
  return my_desc;
}
void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-18-5", "east");
  add_exit("path-17-4", "north");
  add_exit("camp-18-6", "southeast");
  add_exit("camp-17-6", "south");
  add_exit("camp-16-6", "southwest");
  add_exit("camp-16-5", "west");
}
