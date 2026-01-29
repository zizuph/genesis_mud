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
  my_desc += "From the north and the west the camp is bound by a wide rocky "+
    "path. Past the path you can see the mountain ridge coming close.\n";
  add_item("path", "A path goes north of the camp, between it and the "+
           "mountains, disappearing in the west where the mountains seem "+
           "to come to the very shoreline.\n");
  return my_desc;
}
void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-15-5", "west");
  add_exit("path-16-4", "north");
  add_exit("camp-15-6", "southwest");
  add_exit("camp-16-6", "south");
  add_exit("camp-17-6", "southeast");
  add_exit("camp-17-5", "east");
}
