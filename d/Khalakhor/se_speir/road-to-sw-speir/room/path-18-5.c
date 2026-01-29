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
  string my_desc = ::setup_long();
  my_desc += "To the west the path widens significantly, and to you "+
    "notice a military camp being set up. You can either enter it, or "+
    "walk around it to the northwest.\n";
  add_item("camp", "The camp seems to have a half a dozen of large "+
           "tents or so.\n");
  return my_desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-19-5", "east");
  add_exit("path-17-4", "northwest");
  add_exit("camp-17-5", "west");
}
