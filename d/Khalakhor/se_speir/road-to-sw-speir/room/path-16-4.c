/*
 * Path to SW Speir - beginning
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_PATH;

string
setup_long ()
{
  string my_desc = ::setup_camp_long();
  add_item("camp", "The camp seems to have a half a dozen of large "+
           "tents or so, and a couple of dozens of well-armed soldiers.\n");
  return my_desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-15-5", "southwest");
  add_exit("path-17-4", "east");
  add_exit("camp-16-5", "south");
}
