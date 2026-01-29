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
  my_desc += "To the east you notice a change in scenery and realize "+
    "you are getting closer to the plains surrounding Port Macdunn.\n";
  add_item("plains",
           "You feel relaxed seeing finally some abundant greenery.\n");
  
  return my_desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-22-5", "east");
  add_exit("path-20-5", "west");
}
